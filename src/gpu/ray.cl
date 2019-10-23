t_ray ray_init(t_vec3 position, t_vec3 direction)
{
	t_ray ray;

	ray.position = position;
	ray.direction = direction;
	return (ray);
}

t_vec3 ray_reflect(t_vec3 ray, t_vec3 normal)
{
	return (vec3_sub_vec3(
		vec3_mul_n(vec3_mul_n(normal, vec3_dot(normal, ray)), 2.0),
		ray));
}

t_vec3 ray_refract(t_vec3 ray, t_vec3 normal, double n1, double n2)
{
	double k1;
	double k2;
	t_vec3 t;
	double n;
	double a;

	a = acos(vec3_dot(ray, normal));
	n = n1 / n2;
	k1 = cos(a);
	k2 = sqrt(1.0 - pow((n1 / n2), 2.0) * (1 - k1 * k1));
	t = vec3_mul_n(vec3_add_vec3(ray, vec3_mul_n(normal, k1)), n);
	t = vec3_sub_vec3(t, vec3_mul_n(normal, k2));


	/*t = vec3_add_vec3(ray, vec3_mul_n(normal, k1));
	t = vec3_sub_vec3(t, vec3_mul_n(normal, k2));*/

	return (vec3_normalize(t));
}