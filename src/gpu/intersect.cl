void clip(t_object obj, t_ray ray, double *dis, t_trace scene)
{
	int i;
	t_vec3 point;
	t_vec3 vector;
	t_object negative;


	i = 0;
	while (i < scene.oc)
	{
		if (scene.objects[i].model_index == obj.model_index &&
			scene.objects[i].boolean == -1 &&
			scene.objects[i].active)
		{
			negative = scene.objects[i];
			point = vec3_add_vec3(ray.position, vec3_mul_n(ray.direction, *dis));
			vector = vec3_sub_vec3(point, negative.position);
			if (negative.type == 1)
			{
				if (vec3_dot(vector, negative.direction) < 0)
					*dis = -1;
			}
			else if (negative.type == 0)
			{
				if (vec3_length(vector) <= negative.radius)
					*dis = -1;
			}
			else if (negative.type == 2)
			{
				double dot = fabs(vec3_dot(vector, negative.direction));
				double angle = acos(dot / (vec3_length(vector) * vec3_length(negative.direction))) * 180.0 / M_PI;
				if (angle < negative.angle)
					*dis = -1;				
			}
			else if (negative.type == 3)
			{
				double dot = fabs(vec3_dot(vector, negative.direction));
				double proj = dot / vec3_length(negative.direction);
				double x = sqrt(vec3_length(vector) * vec3_length(vector) - proj * proj);
				if (x < negative.radius)
					*dis = -1;
			}
		}
		i++;
	}
}


t_hit closest_intersection(t_trace *trace, t_ray ray, t_range range, int ind, __global t_vec3 *assets)
{
	int i;
	double distances[4];
	t_object obj;
	t_model model;
	t_hit hit;

	hit.distance = INFINITY;
	hit.index = -1;
	i = 0;

	while (i < trace->oc)
	{
		distances[0] = -1;
		distances[1] = -1;
		distances[2] = -1;
		distances[3] = -1;
		obj = trace->objects[i];
		model = trace->models[obj.model_index];

		if (obj.active && i != ind)
		{	
			double k = get_random(&trace->seeds);
			if (k < obj.opacity && obj.boolean == 1)
			{

				if (obj.type == 0) /* sphere */
					intersect_sphere(obj, ray, distances, assets, trace);
				else if (obj.type == 1) /* plane */
					intersect_plane(obj, ray, distances, assets, trace);
				else if (obj.type == 2) /* cone */
					intersect_cone(obj, ray, distances, assets, trace);
				else if (obj.type == 3) /* cylinder */
					intersect_cylinder(obj, ray, distances, assets, trace);
				else if (obj.type == 4) /* disk */
					intersect_disk(obj, ray, distances);
				else if (obj.type == 5) /* polygon */
					intersect_polygon(obj, ray, distances);
				else if (obj.type == 6) /* torus */
					intersect_torus(obj, ray, distances);
				else if (obj.type == 7) /* paraboloid */
					intersect_paraboloid(obj, ray, distances);
				else if (obj.type == 8) /* hyperbooid */
					intersect_hyperboloid(obj, ray, distances);
				if (model.clip)
					clip(obj, ray, &distances[0], *trace);
				if (model.clip && obj.type != 1)
					clip(obj, ray, &distances[1], *trace);
			}
			get_hit(&hit, distances, range, obj, ray, i, assets);
		}
		i++;
	}
	return (hit);
}

void get_hit(t_hit *hit, double distances[4], t_range range, t_object obj, t_ray ray, int i, __global t_vec3 *assets)
{
	int step = 0;

	while (step < 4)
	{
		if (distances[step] >= range.min &&	distances[step] <= range.max && distances[step] < hit->distance)
		{
			hit->distance = distances[step];
			hit->index = i;
			hit->point = vec3_add_vec3(ray.position, vec3_mul_n(ray.direction, hit->distance));
			hit->normal = get_normal(obj, ray_init(hit->point, ray.direction), hit->point, assets);
		}
		step++;
	}
}

void intersect_sphere(t_object obj, t_ray ray, double dis[4], __global t_vec3 *assets, t_trace *trace)
{
	t_vec3 tmp;
	double k[3];

	tmp = vec3_sub_vec3(ray.position, obj.position);
	k[0] = vec3_dot(ray.direction, ray.direction);
	k[1] = 2 * vec3_dot(tmp, ray.direction);
	k[2] = vec3_dot(tmp, tmp) - obj.radius * obj.radius;

	quadratic_solution(k, dis);

	check_transparency(obj, ray, dis, trace, assets);
	check_transparency(obj, ray, dis + 1, trace, assets);
}

void intersect_plane(t_object obj, t_ray ray, double dis[4], __global t_vec3 *assets, t_trace *trace)
{
	t_vec3 n;

	n = obj.direction;
	if (vec3_dot(ray.direction, n) > 0)
		n = vec3_mul_n(n, -1.0);
	if (fabs(vec3_dot(n, ray.direction)) > 0.00001)
		dis[0] = vec3_dot(n,
						  vec3_init(obj.position.x - ray.position.x,
									obj.position.y - ray.position.y,
									obj.position.z - ray.position.z)) /
				 vec3_dot(n, ray.direction);
	else
		dis[0] = -1;	
	check_transparency(obj, ray, dis, trace, assets);
}

void intersect_cone(t_object obj, t_ray ray, double dis[4], __global t_vec3 *assets, t_trace *trace)
{
	t_vec3 t[3];
	double k[3];
	double cos2;
	double sin2;

	obj.direction = vec3_normalize(obj.direction);
	cos2 = pow(cos(obj.angle * M_PI / 180.0), 2.0);
	sin2 = pow(sin(obj.angle * M_PI / 180.0), 2.0);
	t[0] = vec3_sub_vec3(ray.position, obj.position);
	t[1] = vec3_sub_vec3(ray.direction, vec3_mul_n(obj.direction,
												   vec3_dot(ray.direction, obj.direction)));
	t[2] = vec3_sub_vec3(t[0], vec3_mul_n(obj.direction,
										  vec3_dot(t[0], obj.direction)));
	k[0] = cos2 * vec3_dot(t[1], t[1]) -
		   sin2 * pow(vec3_dot(ray.direction, obj.direction), 2.0);
	k[1] = 2 * cos2 * vec3_dot(t[1], t[2]) -
		   2 * sin2 * vec3_dot(ray.direction, obj.direction) *
			   vec3_dot(t[0], obj.direction);
	k[2] = cos2 * vec3_dot(t[2], t[2]) -
		   sin2 * pow(vec3_dot(t[0], obj.direction), 2.0);

	quadratic_solution(k, dis);

	check_transparency(obj, ray, dis, trace, assets);
	check_transparency(obj, ray, dis + 1, trace, assets);
}

void intersect_cylinder(t_object obj, t_ray ray, double dis[4], __global t_vec3 *assets, t_trace *trace)
{
	double k[3];
	t_vec3 t[4];

	obj.direction = vec3_normalize(obj.direction);
	t[0] = vec3_sub_vec3(ray.position, obj.position);
	t[1] = vec3_sub_vec3(ray.direction, vec3_mul_n(obj.direction,
												   vec3_dot(ray.direction, obj.direction)));
	t[2] = vec3_sub_vec3(t[0], vec3_mul_n(obj.direction,
										  vec3_dot(t[0], obj.direction)));
	k[0] = vec3_dot(t[1], t[1]);
	k[1] = 2 * vec3_dot(t[1], t[2]);
	k[2] = vec3_dot(t[2], t[2]) - pow(obj.radius, 2);

	quadratic_solution(k, dis);

	check_transparency(obj, ray, dis, trace, assets);
	check_transparency(obj, ray, dis + 1, trace, assets);
}

void intersect_disk(t_object obj, t_ray ray, double dis[4])
{
	t_vec3 n;
	t_vec3 p;
	double tmp;

	n = obj.direction;
	if (vec3_dot(ray.direction, n) > 0)
		n = vec3_mul_n(n, -1.0);
	dis[0] = INFINITY;
	if (fabs(vec3_dot(n, ray.direction)) > 0.00001)
	{
		tmp = vec3_dot(n,
					   vec3_init(obj.position.x - ray.position.x,
								 obj.position.y - ray.position.y,
								 obj.position.z - ray.position.z)) /
			  vec3_dot(n, ray.direction);
		p = vec3_sub_vec3(obj.position,
						  vec3_add_vec3(ray.position, vec3_mul_n(ray.direction, tmp)));
		if (vec3_length(p) <= obj.radius)
			dis[0] = tmp;
	}
}

void intersect_polygon(t_object obj, t_ray ray, double dis[4])
{
	t_vec3 n;
	t_vec3 p;
	double tmp;

	n = vec3_vec_mul(vec3_sub_vec3(obj.b, obj.a), vec3_sub_vec3(obj.c, obj.a));
	if (vec3_dot(ray.direction, n) > 0)
		n = vec3_mul_n(n, -1.0);

	dis[0] = INFINITY;
	if (fabs(vec3_dot(n, ray.direction)) > 0.00001)
	{
		p = vec3_add_vec3(ray.position,
						  vec3_mul_n(ray.direction,
									 vec3_dot(n, vec3_sub_vec3(obj.a, ray.position)) / vec3_dot(n, ray.direction)));
		tmp = vec3_length(vec3_sub_vec3(p, ray.position));

		if (inside_triangle(p, obj.a, obj.b, obj.c))
			dis[0] = tmp;
	}
}

void intersect_torus(t_object obj, t_ray ray, double dis[4])
{
	double c[5];

	obj.direction = vec3_normalize(obj.direction);
	ray.position = vec3_sub_vec3(ray.position, obj.position);

	c[4] = pow(ray.direction.x * ray.direction.x +
				   ray.direction.y * ray.direction.y +
				   ray.direction.z * ray.direction.z,
			   2.0);
	c[3] = 4.0 * (ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z) *
		   (ray.position.x * ray.direction.x +
			ray.position.y * ray.direction.y +
			ray.position.z * ray.direction.z);
	c[2] = 2.0 * (ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z) *
			   (ray.position.x * ray.position.x +
				ray.position.y * ray.position.y +
				ray.position.z * ray.position.z -
				obj.minor_radius * obj.minor_radius -
				obj.major_radius * obj.major_radius) +
		   4.0 * pow(ray.position.x * ray.direction.x +
						 ray.position.y * ray.direction.y +
						 ray.position.z * ray.direction.z,
					 2.0) +
		   4.0 * obj.major_radius * obj.major_radius *
			   ray.direction.y * ray.direction.y;
	c[1] = 4.0 * (ray.position.x * ray.position.x + ray.position.y * ray.position.y + ray.position.z * ray.position.z - obj.minor_radius * obj.minor_radius - obj.major_radius * obj.major_radius) *
			   (ray.position.x * ray.direction.x +
				ray.position.y * ray.direction.y +
				ray.position.z * ray.direction.z) +
		   8.0 * obj.major_radius * obj.major_radius *
			   ray.position.y * ray.direction.y;
	c[0] = pow(ray.position.x * ray.position.x +
				   ray.position.y * ray.position.y +
				   ray.position.z * ray.position.z -
				   obj.minor_radius * obj.minor_radius -
				   obj.major_radius * obj.major_radius,
			   2.0) -
		   4.0 * obj.major_radius * obj.major_radius *
			   (obj.minor_radius * obj.minor_radius -
				ray.position.y * ray.position.y);
	quartic_solution(c, dis);
}

void intersect_paraboloid(t_object obj, t_ray ray, double dis[4])
{
	double k[3];

	ray.position = vec3_sub_vec3(ray.position, obj.position);
	k[0] = ray.direction.x * ray.direction.x / (obj.surface.x * obj.surface.x) +
		   ray.direction.z * ray.direction.z / (obj.surface.y * obj.surface.y);

	k[1] = 2.0 * ray.position.x * ray.direction.x / (obj.surface.x * obj.surface.x) +
		   2.0 * ray.position.z * ray.direction.z / (obj.surface.y * obj.surface.y) -
		   ray.direction.y;

	k[2] = ray.position.x * ray.position.x / (obj.surface.x * obj.surface.x) +
		   ray.position.z * ray.position.z / (obj.surface.y * obj.surface.y) -
		   ray.position.y;

	quadratic_solution(k, dis);
}

void intersect_hyperboloid(t_object obj, t_ray ray, double dis[4])
{
	double k[3];

	ray.position = vec3_sub_vec3(ray.position, obj.position);
	k[0] = ray.direction.x * ray.direction.x / (obj.surface.x * obj.surface.x) +
		   ray.direction.z * ray.direction.z / (obj.surface.y * obj.surface.y) -
		   ray.direction.y * ray.direction.y / (obj.surface.z * obj.surface.z);

	k[1] = 2.0 * (ray.direction.x * ray.position.x / (obj.surface.x * obj.surface.x) +
				  ray.direction.z * ray.position.z / (obj.surface.y * obj.surface.y) -
				  ray.direction.y * ray.position.y / (obj.surface.z * obj.surface.z));

	k[2] = ray.position.x * ray.position.x / (obj.surface.x * obj.surface.x) +
		   ray.position.z * ray.position.z / (obj.surface.y * obj.surface.y) -
		   ray.position.y * ray.position.y / (obj.surface.z * obj.surface.z) - 1.0;

	quadratic_solution(k, dis);
}
