
t_vec2 vec2_init(double x, double y)
{
	t_vec2 v;
	v.x = x;
	v.y = y;
	return (v);
}

t_vec3 vec3_init(double x, double y, double z)
{
	t_vec3 v;
	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3 vec3_div_n(t_vec3 v, double n)
{
	v.x /= n;
	v.y /= n;
	v.z /= n;
	return (v);
}

t_vec3 vec3_mul_n(t_vec3 v, double n)
{
	v.x *= n;
	v.y *= n;
	v.z *= n;
	return (v);
}

t_vec3 vec3_add_n(t_vec3 v, double n)
{
	v.x += n;
	v.y += n;
	v.z += n;
	return (v);
}

t_vec3 vec3_add_vec3(t_vec3 v1, t_vec3 v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_vec2 vec2_sub_vec2(t_vec2 v1, t_vec2 v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	return (v1);
}

t_vec3 vec3_sub_vec3(t_vec3 v1, t_vec3 v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

t_vec3 vec3_mul_vec3(t_vec3 v1, t_vec3 v2)
{
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
	return (v1);
}

double vec2_length(t_vec2 v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

double vec3_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec2 vec2_normalize(t_vec2 v)
{
	double length;
	length = vec2_length(v);
	v.x /= length;
	v.y /= length;
	return (v);
}

t_vec3 vec3_normalize(t_vec3 v)
{
	float len = vec3_length(v);
	t_vec3 res = vec3_div_n(v, len);
	return (res);
}

double vec2_dot(t_vec2 v1, t_vec2 v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

double vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double vec3_kdot(t_vec3 v1, t_vec3 v2, double k)
{
	double d;
	d = vec3_dot(v1, v2) * k;
	if (d <= 0.0)
		return (0.0);
	if (d >= 1.0)
		return (1.0);
	return (d);
}

t_vec3 vec3_vec_mul(t_vec3 v1, t_vec3 v2)
{
	return (vec3_init(v1.y * v2.z - v1.z * v2.y,
					  v1.z * v2.x - v1.x * v2.z,
					  v1.x * v2.y - v1.y * v2.x));
}

t_vec3 vec3_cross(t_vec3 v1, t_vec3 v2)
{
	return (vec3_init(v1.y * v2.z - v1.z * v2.y,
					  v1.z * v2.x - v1.x * v2.z,
					  v1.x * v2.y - v1.y * v2.x));
}

int is_zero(t_vec3 v)
{
	return (v.x == 0 && v.y == 0 && v.z == 0);
}

t_vec3 rot_x(t_vec3 v, t_vec3 rot, int invert)
{
	t_vec3 res;
	res.x = v.x;
	res.y = v.y * cos(invert * rot.x) + v.z * -sin(invert * rot.x);
	res.z = v.y * sin(invert * rot.x) + v.z * cos(invert * rot.x);
	return (res);
}

t_vec3 rot_y(t_vec3 v, t_vec3 rot, int invert)
{
	t_vec3 res;
	res.x = v.x * cos(invert * rot.y) + v.z * sin(invert * rot.y);
	res.y = v.y;
	res.z = v.x * -sin(invert * rot.y) + v.z * cos(invert * rot.y);
	return (res);
}

t_vec3 rot_z(t_vec3 v, t_vec3 rot, int invert)
{
	t_vec3 res;
	res.x = v.x * cos(invert * rot.z) + v.y * -sin(invert * rot.z);
	res.y = v.x * sin(invert * rot.z) + v.y * cos(invert * rot.z);
	res.z = v.z;
	return (res);
}

t_vec3 vec3_rotate(t_vec3 v, t_vec3 rot, int invert)
{
	v = rot_x(v, rot, invert);
	v = rot_y(v, rot, invert);
	v = rot_z(v, rot, invert);
	return (v);
}

double vec3_distance(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v;

	v = vec3_init(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
