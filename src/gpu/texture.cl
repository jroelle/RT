
t_vec3	texture(t_object obj, t_vec3 point, __global t_vec3 *assets)
{
	if (obj.type == 0)
		return (texture_sphere(obj, point, obj.texture, assets));
	if (obj.type == 1)
		return (texture_plane(obj, point, obj.texture, assets));
	if (obj.type == 2)
		return (texture_cone(obj, point, obj.texture, assets));
	if (obj.type == 3)
		return (texture_cylinder(obj, point, obj.texture, assets));
	return (vec3_init(0, 0, 0));
}

t_vec3	texture_sphere(t_object obj, t_vec3 point, t_texture texture, __global t_vec3 *assets)
{
		t_vec3 hitpoint;
		float u;
		float v;
		int i_u;
		int i_v;

		hitpoint = vec3_div_n(vec3_sub_vec3(point, obj.position), obj.radius);
		v = 0.5 + atan2(hitpoint.z, hitpoint.x) / (2.0 * M_PI);
		u = 0.5 - asin(hitpoint.y) / M_PI;
		i_u = (int)((float)(texture.height) * u);
		i_v = (int)((float)(texture.width) * v);
		i_u = (int)((float)(i_u + texture.dy)/ texture.scale) % texture.height;
		i_v = (int)((float)(i_v + texture.dx)/ texture.scale) % texture.width;
		return assets[texture.position + i_u * texture.width + i_v];
}

t_vec3 texture_torus(t_object obj, t_vec3 point, t_texture texture, __global t_vec3 *assets)
{
		t_vec3 hitpoint;
		float u;
		float v;
		int i_u;
		int i_v;

		hitpoint.x = (point.x - obj.position.x) / obj.minor_radius;
		hitpoint.y = (point.y - obj.position.y) / obj.minor_radius;
		hitpoint.z = (point.z - obj.position.z) / obj.minor_radius;
		v = 0.5 + atan2(hitpoint.z, hitpoint.x) / (2.0 * M_PI);
		u = 0.5 + atan2(hitpoint.y,
						pow(hitpoint.x * hitpoint.x + hitpoint.z * hitpoint.z, 
						0.5) - obj.major_radius) / (2.0 * M_PI);
		i_u = (int)((float)(obj.texture.height - 1) * u);
		i_v = (int)((float)(obj.texture.width - 1) * v);
return assets[texture.position + i_u * texture.width + i_v];
}

t_vec3 texture_cylinder(t_object obj, t_vec3 point, t_texture texture, __global t_vec3 *assets)
{
		t_vec3 hitpoint;
		float u;
		float v;
		int i_u;
		int i_v;

		hitpoint = vec3_div_n(vec3_sub_vec3(point, obj.position), obj.radius);
		u = 0.5 + atan2(hitpoint.z, hitpoint.x) / (2.0 * M_PI);
		v = 0.5 * hitpoint.y / M_PI;
		v -= floor(v);
		v = 1.0 - v;
		i_u = (int)((float)(texture.height) * u);
		i_v = (int)((float)(texture.width) * v);
		i_u = (int)((float)(i_u - texture.dx) / texture.scale) % texture.width;
		i_v = (int)((float)(i_v - texture.dy) / texture.scale) % texture.height;
        return assets[texture.position + i_v * texture.height + i_u];
}

t_vec3 texture_cone(t_object obj, t_vec3 point, t_texture texture, __global t_vec3 *assets)
{
		t_vec3 hitpoint;
		float u;
		float v;
		int i_u;
		int i_v;

		hitpoint = vec3_sub_vec3(point, obj.position);
		u = 0.5 + atan2(hitpoint.z, hitpoint.x) / (2.0 * M_PI);
		v = 0.5 * hitpoint.y / M_PI;
		v -= floor(v);
		v = 1.0 - v;
		i_u = (int)((float)(texture.height) * u);
		i_v = (int)((float)(texture.width) * v);
		i_u = (int)((float)(i_u - texture.dx) / texture.scale) % texture.width;
		i_v = (int)((float)(i_v - texture.dy) / texture.scale) % texture.height;
        return assets[texture.position + i_v * texture.height + i_u];
}

t_vec3 texture_plane(t_object obj, t_vec3 point, t_texture texture, __global t_vec3 *assets)
{
	t_vec3 hitpoint;
	
	t_vec3 oz = vec3_vec_mul(vec3_init(1, 0, 0), obj.direction);
	
	if (is_zero(oz))
		oz = vec3_init(0, 0, 1);
	oz = vec3_normalize(oz);

	t_vec3 ox = vec3_normalize(vec3_vec_mul(oz, obj.direction));

	hitpoint.x = point.x - obj.position.x;
	hitpoint.y = point.y - obj.position.y;
	hitpoint.z = point.z - obj.position.z;

	float len = vec3_length(hitpoint);
	hitpoint = vec3_normalize(hitpoint);

	float cosz = vec3_dot(oz, hitpoint);
	float sinx = vec3_dot(ox, hitpoint);

	float dx = len * sinx * texture.height / texture.width;
	float dy = len * cosz;
	float t = dx / texture.scale;
		
		if (t < 0)
		{
			t = fabs(floor(dx / texture.scale));
			dx += t * texture.scale;
		}
		else
			dx -= floor(t) * texture.scale;

		t = dy / texture.scale;

		if (t < 0)
		{
			t = fabs(floor(dy / texture.scale));
			dy += t * texture.scale;
		}
		else
			dy -= floor(t) * texture.scale;

		int i_dy = (int)((float)(texture.height) * dy / texture.scale);
		int i_dx = (int)((float)(texture.width) * dx / texture.scale);

		i_dy = (i_dy - texture.dy) % texture.height;
		i_dx = (-i_dx - texture.dx) % texture.width;
		i_dx = i_dx > (int)texture.width ? 0 : i_dx;
		i_dy = i_dy > (int)texture.height ? 0 : i_dy;
    return assets[(texture.position + i_dy * texture.width + i_dx)];
}
