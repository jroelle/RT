t_vec3 point_color(t_model model, t_object obj, t_vec3 point, __global t_vec3 *assets)
{
	if (obj.proc_tex > 0 && obj.proc_tex <= 3)
	 	return (procedural_texture(obj, point, assets));
	if (obj.texture.index > -1)
		return (texture(obj, point, assets));
	return (model.color);
}

void new_shade(t_trace *trace, t_shade *shader, __global t_vec3 *assets)
{
    t_hit hit;
    t_object obj;
    t_model model;
    t_vec3 albedo;
    double specular;
    double diff_chance;
    double spec_chance;
    double sum;
    double roulette;
    double n1;
    double n2;
    double k;
    double alpha;
    double f;
    t_vec3 color;

    hit = closest_intersection(trace, trace->ray, trace->range, shader->stack[19], assets);

    if (hit.index == -1)
    {
        shader->state++;
        return;
    }

    obj = trace->objects[hit.index];
    model = trace->models[obj.model_index];
    color = vec3_add_vec3(point_color(model, obj, hit.point, assets), trace->ambience);

    if (model.light)
    {
        if (shader->bounceIsSpecular)
        {
            shader->accumCol = vec3_mul_vec3(shader->maskEyePath, vec3_mul_n(color, model.light));
            shader->skipConnectionLightPath = 1;
        }
        shader->state++;
        return;
    }

    n1 = 0;
    n2 = 0;
    k = 1;
    shader->stack[19] = hit.index;
    if (model.refractive_index != 1)
    {
        shader->stack[19] = -1;
        if (!shader->stack[0])
        {
            shader->stack[0]++;
            shader->stack[shader->stack[0]] = hit.index;
            n1 = 1;
            n2 = model.refractive_index;
        }
        else
        {
            if (shader->stack[shader->stack[0]] == hit.index)
            {
                shader->stack[0]--;
                n1 = model.refractive_index;
                if (!shader->stack[0])
                    n2 = 1;
                else
                    n2 = trace->models[shader->stack[0]].refractive_index;
                shader->stack[19] = hit.index;
            }
            else
            {
                if (!shader->stack[0])
                    n1 = 1;
                else
                    n1 = trace->models[shader->stack[0]].refractive_index;
                n2 = model.refractive_index;
                shader->stack[0]++;
                shader->stack[shader->stack[0]] = hit.index;
            }
        }
    }

    trace->ray.position = hit.point;

    specular = model.specular;
    albedo.x = min(1.0 - specular, color.x);
    albedo.y = min(1.0 - specular, color.y);
    albedo.z = min(1.0 - specular, color.z);

    diff_chance = (albedo.x + albedo.y + albedo.z) / 3.0;
    spec_chance = specular;
    sum = diff_chance + spec_chance;
    diff_chance /= sum;
    spec_chance /= sum;

    

    if ((n1 && n1 != 1) || (n2 && n2 != 1))
        k = reflection_coefficient(trace->ray.direction, hit.normal, n1, n2);
        
    roulette = get_random(&trace->seeds);
    if (roulette < 1.0 - k) /* refract 3 */
    {
        shader->bounceIsSpecular = true;
        shader->previousIntersecType = 3;
        shader->maskEyePath = vec3_mul_vec3(shader->maskEyePath, color);
        trace->ray.direction = ray_refract(trace->ray.direction, hit.normal, n1, n2);
        if (shader->state)
            shader->state++;
    }
    else
    {
        roulette = get_random(&trace->seeds);
        if (roulette < spec_chance) /* specular 2 */
        {
            shader->maskEyePath = vec3_mul_vec3(shader->maskEyePath, color);
            shader->bounceIsSpecular = true;
            shader->previousIntersecType = 2;

            alpha = pow(10000.0, model.reflective * model.reflective);
            f = (alpha + 2.0) / (alpha + 1.0);
            trace->ray.direction = ray_reflect(vec3_mul_n(trace->ray.direction, -1.0), hit.normal);
            trace->ray.direction = ray_random(trace->ray.direction, alpha, &trace->seeds);
            if (shader->state)
                shader->state++;
        }
        else /* diffuse 1 */
        {
            if (shader->state) /* это уже из лампы */
            {
                shader->nlLightPath = vec3_normalize(hit.normal);
                shader->nlLightPath = vec3_dot(shader->nlLightPath, shader->lightRay.direction) < 0.0 ? shader->nlLightPath : vec3_mul_n(shader->nlLightPath, -1.0);
                shader->lightX = hit.point;
                shader->state++;
                shader->maskLightPath = vec3_mul_n(shader->maskLightPath, vec3_dot(shader->nlLightPath, vec3_mul_n(shader->lightRay.direction, -1)));
                return;
            }

            shader->maskEyePath = vec3_mul_vec3(shader->maskEyePath, color);
            shader->eyeX = hit.point;
            shader->nlEyePath = vec3_normalize(hit.normal);
            shader->nlEyePath = vec3_dot(shader->nlEyePath, trace->ray.direction) < 0.0 ? shader->nlEyePath : vec3_mul_n(shader->nlEyePath, -1.0);
            shader->skipConnectionLightPath = false;
            shader->eyeIndex = hit.index;
            shader->diffuseCount++;

            if (shader->diffuseCount > 1 || get_random(&trace->seeds) < 0.5)
            {
                shader->state = 1;
                return;
            }
            shader->bounceIsSpecular = 0;
            shader->previousIntersecType = 1;

            trace->ray.direction = ray_random(hit.normal, 1.0, &trace->seeds);
        }
    }
}

t_vec3 trace_ray(t_trace *trace, __global t_vec3 *assets)
{
    int i;
    t_shade shader;
    shader.accumCol = vec3_init(0, 0, 0);
    shader.maskEyePath = vec3_init(1, 1, 1);
    shader.maskLightPath = vec3_init(1, 1, 1);
    shader.eyeX = vec3_init(0, 0, 0);
    shader.lightX = vec3_init(0, 0, 0);
    shader.nlEyePath = vec3_init(0, 0, 0);
    shader.nlLightPath = vec3_init(0, 0, 0);
    shader.previousIntersecType = -1;
    shader.bounceIsSpecular = 1;
    shader.skipConnectionLightPath = 1;
    shader.diffuseCount = 0;
    shader.state = 0;
    shader.stack[0] = 0;
    shader.stack[19] = -1;

    i = 0;

    while (!shader.state && i < trace->depth)
    {
        new_shade(trace, &shader, assets);
        trace->range.min = 0.0;
        i++;
    }
    shader.state = 1;

    if (shader.skipConnectionLightPath)
        return shader.accumCol;

    get_random_light_ray(trace, &shader);

    shader.stack[0] = 0;
    shader.stack[19] = shader.lightObejctIndex;
    trace->ray = shader.lightRay;

    new_shade(trace, &shader, assets);

    /*i = 0;
    while (i < trace->depth)
    {
        new_shade(trace, &shader);
        trace->range.min = 0.0;
        if (shader.skipConnectionLightPath)
            return shader.accumCol;

        get_random_light_ray(trace, &shader);

        shader.stack[0] = 0;
        shader.stack[19] = shader.lightObejctIndex;
        trace->ray = shader.lightRay;
        i++;
    }*/

    t_vec3 dir = vec3_sub_vec3(shader.lightX, shader.eyeX);
    dir = vec3_normalize(dir);

    shader.connectRay = ray_init(shader.eyeX, dir);

    t_hit hit = closest_intersection(trace, shader.connectRay, trace->range, shader.eyeIndex, assets);
 
    float d1 = vec3_distance(shader.eyeX, hit.point);
    float d2 = vec3_distance(shader.eyeX, shader.lightX);

    if (fabs(d1 - d2) > 0.00001)
    {
        return shader.accumCol;
    }
    else
    {
        float eyeDot = vec3_dot(shader.connectRay.direction, shader.nlEyePath);
        if (eyeDot < 0.0)
            shader.maskEyePath = vec3_init(0, 0, 0);
        shader.maskEyePath = vec3_mul_n(shader.maskEyePath, eyeDot);
        if (vec3_dot(vec3_mul_n(shader.connectRay.direction, -1), shader.nlLightPath) < 0.0)
            shader.maskLightPath = vec3_init(0, 0, 0);
        shader.maskLightPath = vec3_mul_n(shader.maskLightPath, vec3_dot(vec3_mul_n(shader.connectRay.direction, -1), shader.nlLightPath));
        shader.accumCol = vec3_mul_vec3(shader.maskEyePath, shader.maskLightPath);
    }
    return shader.accumCol;
}

int get_random_light_model_index(t_trace *trace)
{
	int count_of_light = 0;
	int i = 0;
	while (i < trace->mc)
	{
		if (trace->models[i].light)
			count_of_light++;
		i++;
	}
	double roulette = get_random(&trace->seeds);
	double shift = 1.0 / count_of_light;
	double f = shift;
	count_of_light = 0;
	while (f < 1)
	{
		if (roulette < f)
		{
			break;
		}
		count_of_light++;
		f += shift;
	}
	return (count_of_light);
}

int get_random_light_object_index(t_trace *trace, int model_ind)
{
	int i = 0;
	int j = 0;
	while (i < trace->mc)
	{
		if (trace->models[i].light)
		{
			if (j == model_ind)
			{
				break;
			}
			j++;
		}
		i++;
	}
	j = 0;
	while (j < trace->oc)
	{
		if (trace->objects[j].model_index == i)
			break;
		j++;
	}
	return (j);
}

t_vec3 get_random_object_point(t_trace *trace, int obj_ind)
{
    t_vec3 point;

	if (trace->objects[obj_ind].type == 4) /*disk*/
	{
		double r1;
		r1 = get_random(&trace->seeds) * trace->objects[obj_ind].radius;
        t_vec3 dir = trace->objects[obj_ind].direction;
		point = ray_random(vec3_normalize(dir), 1, &trace->seeds);
        t_vec3 pos = trace->objects[obj_ind].position;
		point = vec3_add_vec3(pos, vec3_mul_n(vec3_normalize(vec3_vec_mul(point, dir)), r1));
	}
    else if (trace->objects[obj_ind].type == 0)
    {
        double coin = get_random(&trace->seeds);
        t_vec3 center = trace->objects[obj_ind].position;
        t_vec3 ray = ray_random(vec3_init(0, 1, 0), 0, &trace->seeds);
        // t_vec3 ray = vec3_normalize(vec3_init(get_random(&trace->seeds), get_random(&trace->seeds), get_random(&trace->seeds)));
        if (coin > 0.5)
            ray = vec3_mul_n(ray, -1);
        point = vec3_add_vec3(center, vec3_mul_n(ray, trace->objects[obj_ind].radius));
    }
	return (point);
}

t_vec3 randomCosWeightedDirectionInHemisphere(t_trace *trace, t_vec3 nl)
{
	float r1 = M_PI * 2.0 * get_random(&trace->seeds);
	float r2 = get_random(&trace->seeds);
	float r2s = sqrt(r2);

	t_vec3 w = nl;
	t_vec3 u;
	if (fabs(w.x) > 0.1)
		u = vec3_cross(vec3_init(0.0, 1.0, 0.0), w);
	else
		u = vec3_cross(vec3_init(1.0, 0.0, 0.0), w);

	u = vec3_normalize(u);
	t_vec3 v = vec3_cross(w, u);
	return vec3_normalize(
		vec3_add_vec3(vec3_mul_n(u, cos(r1) * r2s), 
		vec3_add_vec3(vec3_mul_n(v, sin(r1) * r2s), vec3_mul_n(w, sqrt(1.0 - r2)))));
}

void	get_random_light_ray(t_trace *trace, t_shade *shader)
{
	shader->lightObejctIndex = get_random_light_object_index(trace, get_random_light_model_index(trace));
	shader->lightModelIndex = trace->objects[shader->lightObejctIndex].model_index;
    t_vec3 color = trace->models[shader->lightModelIndex].color;
    float light = trace->models[shader->lightModelIndex].light;
	shader->lightEmission = vec3_mul_n(color, light);
    shader->lightPoint = get_random_object_point(trace, shader->lightObejctIndex);
    t_vec3 dir;
    if (trace->objects[shader->lightObejctIndex].type == 0)
        dir = vec3_init(0, 0, -1);
    else
        dir = trace->objects[shader->lightObejctIndex].direction;
	shader->nlLightPath = vec3_normalize(dir); /*HARDCODE LIGHT NORMAL !!!!*/
	shader->lightRay = ray_init(shader->lightPoint, randomCosWeightedDirectionInHemisphere(trace, shader->nlLightPath));
	shader->maskLightPath = shader->lightEmission;
	shader->lightX = shader->lightPoint;
}

