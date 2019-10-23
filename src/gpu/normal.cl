t_vec3 wave(t_object obj, t_vec3 point, t_vec3 normal)
{
	t_vec3 shift;
	t_vec3 res;


	if (fabs(normal.x) > 0.99 && fabs(normal.y) < 0.001 && fabs(normal.z) < 0.001)
	{
		shift.x = cos(point.z * 0.3);
		shift.y = sin(point.z * 0.3);
	}
	else
	{
		shift.x = cos(point.x * 0.3);
		shift.y = sin(point.x * 0.3);
	}
	shift.z = 2;
	shift = vec3_normalize(shift);

    t_vec3 oz = vec3_vec_mul(vec3_init(0, -1, 0), normal);
    if (is_zero(oz))
        oz = vec3_init(0, 0, 1);
    else
        oz = vec3_normalize(oz);

    t_vec3 ox = vec3_normalize(vec3_vec_mul(oz, normal));

    res.x = shift.x * oz.x + shift.y * ox.x + shift.z * normal.x;
    res.y = shift.x * oz.y + shift.y * ox.y + shift.z * normal.y;
    res.z = shift.x * oz.z + shift.y * ox.z + shift.z * normal.z;

	return (res);
}

t_vec3 map_plane(t_object obj, t_vec3 point, t_vec3 normal, __global t_vec3 *assets)
{
		t_vec3 color = texture_plane(obj, point, obj.map, assets);

		t_vec3 shift;
		shift.x = color.x * 2.0 - 1.0;
		shift.y = color.y * 2.0 - 1.0;
		shift.z = color.z * 2.0 - 1.0;
		shift = vec3_normalize(shift);

		t_vec3 res;
		t_vec3 oz = vec3_vec_mul(vec3_init(0, -1, 0), normal);
		if (is_zero(oz))
			oz = vec3_init(0, 0, 1);

		t_vec3 ox;
		if (oz.x > 0)
			ox = vec3_normalize(vec3_vec_mul(oz, normal));
		else
			ox = vec3_normalize(vec3_vec_mul(normal, oz));

		res.x = shift.x * oz.x + shift.y * ox.x + shift.z * normal.x;
		res.y = shift.x * oz.y + shift.y * ox.y + shift.z * normal.y;
		res.z = shift.x * oz.z + shift.y * ox.z + shift.z * normal.z;

		return (res);
}

t_vec3 map_sphere(t_object obj, t_vec3 point, t_vec3 normal, __global t_vec3 *assets)
{
		t_vec3 color = texture_sphere(obj, point, obj.map, assets);

		t_vec3 shift;
		shift.x = color.x * 2.0 - 1.0;
		shift.y = color.y * 2.0 - 1.0;
		shift.z = color.z * 2.0 - 1.0;

		shift = vec3_normalize(shift);

		t_vec3 res;
		t_vec3 oz = vec3_vec_mul(vec3_init(0, -1, 0), normal);
		if (is_zero(oz))
			oz = vec3_init(0, 0, 1);
		
		t_vec3 ox;
		if (oz.x > 0)
			ox = vec3_normalize(vec3_vec_mul(normal, oz));
		else
			ox = vec3_normalize(vec3_vec_mul(oz, normal));
		if (is_zero(ox))
			ox = vec3_init(1, 0, 0);

		res.x = shift.x * oz.x + shift.y * ox.x + shift.z * normal.x;
		res.y = shift.x * oz.y + shift.y * ox.y + shift.z * normal.y;
		res.z = shift.x * oz.z + shift.y * ox.z + shift.z * normal.z;

		return (res);
}

t_vec3 map_cylinder(t_object obj, t_vec3 point, t_vec3 normal, __global t_vec3 *assets)
{
		t_vec3 color = texture_cylinder(obj, point, obj.map, assets);

		t_vec3 shift;
		shift.x = color.x * 2.0 - 1.0;
		shift.y = color.y * 2.0 - 1.0;
		shift.z = color.z * 2.0 - 1.0;

		shift = vec3_normalize(shift);

		t_vec3 res;
		t_vec3 oz = vec3_vec_mul(vec3_init(0, -1, 0), normal);
		if (is_zero(oz))
			oz = vec3_init(1, 0, 0);

		t_vec3 ox = vec3_normalize(vec3_vec_mul(normal, oz));

		res.x = shift.x * oz.x + shift.y * ox.x + shift.z * normal.x;
		res.y = shift.x * oz.y + shift.y * ox.y + shift.z * normal.y;
		res.z = shift.x * oz.z + shift.y * ox.z + shift.z * normal.z;

		if (vec3_dot(normal, res) > 0)
			res = vec3_mul_n(res, -1);

		return (res);
}

t_vec3 map_cone(t_object obj, t_vec3 point, t_vec3 normal, __global t_vec3 *assets)
{
		t_vec3 color = texture_cone(obj, point, obj.map, assets);

		t_vec3 shift;
		shift.x = color.x * 2.0 - 1.0;
		shift.y = color.y * 2.0 - 1.0;
		shift.z = color.z * 2.0 - 1.0;

		shift = vec3_normalize(shift);

		t_vec3 res;
		t_vec3 oz = vec3_vec_mul(vec3_init(0, -1, 0), normal);
		if (is_zero(oz))
			oz = vec3_init(1, 0, 0);

		t_vec3 ox = vec3_normalize(vec3_vec_mul(normal, oz));

		res.x = shift.x * oz.x + shift.y * ox.x + shift.z * normal.x;
		res.y = shift.x * oz.y + shift.y * ox.y + shift.z * normal.y;
		res.z = shift.x * oz.z + shift.y * ox.z + shift.z * normal.z;

		if (vec3_dot(normal, res) > 0)
			res = vec3_mul_n(res, -1);

		return (res);
}

t_vec3 normal_map(t_object obj, t_vec3 point, t_vec3 normal, __global t_vec3 *assets)
{
	if (obj.type == 0)
		return (map_sphere(obj, point, normal, assets));
	if (obj.type == 1)
		return (map_plane(obj, point, normal, assets));
	if (obj.type == 2)
		return (map_cone(obj, point, normal, assets));
	if (obj.type == 3)
		return (map_cylinder(obj, point, normal, assets));
	/* if (obj.type == 6)
	 	return (map_torus(obj, point, normal));*/
	return (vec3_init(0, 0, 0));
}

t_vec3 get_normal(t_object obj, t_ray ray, t_vec3 point, __global t_vec3 *assets)
{

	t_vec3 n;
	double a;

	n = vec3_init(0.0, 0.0, 0.0);
	
	if (obj.type == 0) /* sphere */
	{
		n = vec3_sub_vec3(ray.position, obj.position);
	}
	else if (obj.type == 1 || obj.type == 4) /* plane, disk */
	{
		n = obj.direction;
		if (vec3_dot(ray.direction, obj.direction) > 0)
			n = vec3_mul_n(n, -1.0);
	}
	else if (obj.type == 2) /* cone */
	{
		n = vec3_vec_mul(
			vec3_vec_mul(
				vec3_sub_vec3(obj.position, ray.position),
				obj.direction),
			vec3_sub_vec3(obj.position, ray.position));
		if (vec3_dot(
				vec3_sub_vec3(obj.position, ray.position),
				obj.direction) < 0)
			n = vec3_mul_n(n, -1.0);
	}
	else if (obj.type == 3) /* cylinder */
	{
		n = vec3_vec_mul(
			vec3_vec_mul(
				vec3_sub_vec3(obj.position, ray.position),
				obj.direction),
			obj.direction);
	}
	else if (obj.type == 5) /* polygon */
	{
		n = vec3_vec_mul(
			vec3_sub_vec3(obj.b, obj.a),
			vec3_sub_vec3(obj.c, obj.a));
		if (vec3_dot(ray.direction, obj.direction) > 0)
			n = vec3_mul_n(n, -1.0);
	}
	else if (obj.type == 6) /* torus */
	{
		a = 1.0 - obj.major_radius / sqrt(point.x * point.x + point.z * point.z);
		n = vec3_init(point.x * a, point.y, point.z * a);
	}
	else if (obj.type == 7) /* paraboloid */
	{
		n = vec3_init(2.0 * point.x / (obj.surface.x * obj.surface.x),
					  -1.0, 2.0 * point.z / (obj.surface.y * obj.surface.y));
	}
	else if (obj.type == 8) /* hyperboloid */
	{
		n = vec3_init(2.0 * point.x / (obj.surface.x * obj.surface.x),
					  -2.0 * point.y / (obj.surface.z * obj.surface.z),
					  2.0 * point.z / (obj.surface.y * obj.surface.y));
	}
	n = vec3_normalize(n);
	if (obj.map.index > -1)
		return (normal_map(obj, point, n, assets));
	if (obj.wave)
		return (wave(obj, point, n));
	return (vec3_normalize(n));
}