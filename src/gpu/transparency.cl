double transparency_map(t_object obj, t_vec3 point, __global t_vec3 *assets)
{
	if (obj.type == 0)
		return (texture_sphere(obj, point, obj.transparency, assets).x);
	if (obj.type == 1)
		return (texture_plane(obj, point, obj.transparency, assets).x);
	if (obj.type == 2)
		return (texture_cone(obj, point, obj.transparency, assets).x);
	if (obj.type == 3)
		return (texture_cylinder(obj, point, obj.transparency, assets).x);
	return (1);
}

void check_transparency(t_object obj, t_ray ray, double *dis, t_trace *trace, __global t_vec3 *assets)
{
	t_vec3 point;
	double r;

	if (obj.transparency.index > -1)
	{
		point = vec3_add_vec3(ray.position, vec3_mul_n(ray.direction, *dis));
		r = get_random(&trace->seeds);
		if (r > transparency_map(obj, point, assets))
			*dis = -1;
	}
}
