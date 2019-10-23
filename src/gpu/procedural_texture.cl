double smootherstep(double x)
{
	return (6.0 * pow(x, 5.0) - 15.0 * pow(x, 4.0) + 10.0 * pow(x, 3.0));
}

double lerp(double a, double b, double t)
{
	return (a + smootherstep(t) * (b - a));
}

t_vec3 get_noise(__global t_vec3 *noise, int x, int y, t_texture texture)
{
	// x, y - texture coordinates
	// (now they are pixels)
	int i;
	int j;
	t_vec2 coord;
	double top_left;
	double top_right;
	double bottom_left;
	double bottom_right;

	// x, y -> indexes in noise array
	j = x / (TEXTURE_WIDTH / (texture.width - 1));
	i = y / (TEXTURE_HEIGHT / (texture.height - 1));
	// printf("j: %d = %d / (%d / %d))\ni: %d = %d / (%d / %d))\n",
	// j, x, TEXTURE_WIDTH, texture.width - 1,
	// i, y, TEXTURE_HEIGHT, texture.height - 1);

	// x, y -> position in the square
	coord.x = x % (TEXTURE_WIDTH / (texture.width - 1));
	coord.y = y % (TEXTURE_HEIGHT / (texture.height - 1));

	// coord -> [0, 1]
	coord.x /= (double)TEXTURE_WIDTH / (texture.width - 1);
	coord.y /= (double)TEXTURE_HEIGHT / (texture.height - 1);
	coord.y = 1.0 - coord.y;

	t_vec2 distance_to_top_left = vec2_sub_vec2(coord, vec2_init(0, 1));
	t_vec2 distance_to_top_right = vec2_sub_vec2(coord, vec2_init(1, 1));
	t_vec2 distance_to_bottom_left = vec2_sub_vec2(coord, vec2_init(0, 0));
	t_vec2 distance_to_bottom_right = vec2_sub_vec2(coord, vec2_init(1, 0));

	t_vec2 noise_i_j = vec2_init(noise[texture.position + i * texture.width + j].x,
		noise[texture.position + i * texture.width + j].y);
	t_vec2 noise_i_j1 = vec2_init(noise[texture.position + i * texture.width + j + 1].x,
		noise[texture.position + i * texture.width + j + 1].y);
	t_vec2 noise_i1_j = vec2_init(noise[texture.position + (i + 1) * texture.width + j].x,
		noise[texture.position + (i + 1) * texture.width + j].y);
	t_vec2 noise_i1_j1 = vec2_init(noise[texture.position + (i + 1) * texture.width + j + 1].x,
		noise[texture.position + (i + 1) * texture.width + j + 1].y);

	top_left = vec2_dot(noise_i_j, distance_to_top_left);
	top_right = vec2_dot(noise_i_j1, distance_to_top_right);
	bottom_left = vec2_dot(noise_i1_j, distance_to_bottom_left);
	bottom_right = vec2_dot(noise_i1_j1, distance_to_bottom_right);

	double top = lerp(top_left, top_right, coord.x);
	double bottom = lerp(bottom_left, bottom_right, coord.x);
	double tb = (lerp(bottom, top, coord.y) + 1.414) / 2.828;

	return (vec3_init(tb, tb, tb));
}


t_vec3 chess_board(int x, int y, t_texture texture)
{
	t_vec3 white;
	t_vec3 black;
	unsigned int x_cell;
	unsigned int y_cell;

	black = vec3_init(0, 0, 0);
	white = vec3_init(1, 1, 1);

	x_cell = x / (TEXTURE_WIDTH / 10);
	y_cell = y / (TEXTURE_HEIGHT / 10);

	if ((x_cell % 2 && y_cell % 2) || (!(x_cell % 2) && !(y_cell % 2)))
		return (black);
	return (white);
}

t_vec3 brick_wall(int x, int y, t_texture texture)
{
	t_vec3 white;
	t_vec3 red;
	unsigned int x_cell;
	unsigned int y_cell;
	unsigned int edge;

	white = vec3_init(1, 1, 1);
	red = vec3_init(0.6, 0.2, 0.2);

	x_cell = x / (TEXTURE_WIDTH / 4);
	y_cell = y / (TEXTURE_HEIGHT / 8);
	if (y_cell % 2)
	{
		if (x - x_cell * (TEXTURE_WIDTH / 4) < TEXTURE_WIDTH / 8)
			x += TEXTURE_WIDTH / 8;
		else
			x -= TEXTURE_WIDTH / 8;
	}
	edge = TEXTURE_WIDTH / 50;

	if (x - x_cell * (TEXTURE_WIDTH / 4) < edge || y - y_cell * (TEXTURE_HEIGHT / 8) < edge)
		return (white);
	return (red);
}

t_vec3 choose_procedural_texture(__global t_vec3 *noise, int proc_tex, int x, int y, t_texture texture)
{
		if (proc_tex == 1)
			return (get_noise(noise, abs(x), abs(y), texture));
		if (proc_tex == 2)
			return (chess_board(x, y, texture));
		return (brick_wall(x, y, texture));
}

t_vec3 procedural_texture_sphere(__global t_vec3 *noise, t_object obj, t_vec3 point)
{
		t_vec3 hitpoint;
		hitpoint = vec3_div_n(vec3_sub_vec3(point, obj.position), obj.radius);

		float v = 0.5 + atan2(hitpoint.z, hitpoint.x) / (2.0 * M_PI);
		float u = 0.5 - asin(hitpoint.y) / M_PI;

		int i_u = (int)((float)(TEXTURE_HEIGHT) * u);
		int i_v = (int)((float)(TEXTURE_WIDTH) * v);

		i_u = (int)((float)(i_u + obj.texture.dy) / obj.texture.scale) % TEXTURE_HEIGHT;
		i_v = (int)((float)(i_v + obj.texture.dx) / obj.texture.scale) % TEXTURE_WIDTH;
		return (choose_procedural_texture(noise, obj.proc_tex, i_v, i_u, obj.texture));
}

t_vec3 procedural_texture_plane(__global t_vec3 *noise, t_object obj, t_vec3 point)
{
		t_vec3 hitpoint;
		
		t_vec3 oz = vec3_vec_mul(vec3_init(1,0,0), obj.direction);
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

		float dx = len * cosz;
		float dy = len * sinx;
		float t = dx / obj.texture.scale;
		
		if (t < 0)
		{
			t = fabs(floor(dx / obj.texture.scale));
			dx += t * obj.texture.scale; 
		}
		else
			dx -= floor(t) * obj.texture.scale; 
		t = dy / obj.texture.scale;
		if (t < 0)
		{
			t = fabs(floor(dy / obj.texture.scale));
			dy += t * obj.texture.scale; 
		}
		else
			dy -= floor(t) * obj.texture.scale;

		int i_dy = (int)((float)(TEXTURE_HEIGHT) * dy / obj.texture.scale);
		int i_dx = (int)((float)(TEXTURE_WIDTH) * dx / obj.texture.scale);

		i_dy = (i_dy + obj.texture.dy) % TEXTURE_HEIGHT;
		i_dx = (i_dx + obj.texture.dx) % TEXTURE_WIDTH;

		return (choose_procedural_texture(noise, obj.proc_tex, i_dx, i_dy, obj.texture));
}

t_vec3 procedural_texture_cylinder(__global t_vec3 *noise, t_object obj, t_vec3 point)
{
		t_vec3 hitpoint;

		hitpoint = vec3_div_n(vec3_sub_vec3(point, obj.position), obj.radius);

		float u = 0.5 + atan2(hitpoint.z, hitpoint.x) / (2.0 * M_PI);
		float v = 0.5 * hitpoint.y / M_PI;
		v -= floor(v);

		int i_u = (int)((float)(TEXTURE_HEIGHT) * u);
		int i_v = (int)((float)(TEXTURE_WIDTH) * v);

		i_u = (int)((float)(i_u + obj.texture.dy) * 2.0 / obj.texture.scale) % TEXTURE_HEIGHT;
		i_v = (int)((float)(i_v + obj.texture.dx) * 2.0 / obj.texture.scale) % TEXTURE_WIDTH;

		return (choose_procedural_texture(noise, obj.proc_tex, i_u, i_v, obj.texture));
}

t_vec3 procedural_texture_cone(__global t_vec3 *noise, t_object obj, t_vec3 point)
{
		t_vec3 hitpoint = vec3_sub_vec3(point, obj.position);

		float u = 0.5 + atan2(hitpoint.z, hitpoint.x) / (2.0 * M_PI);
		float v = 0.5 * hitpoint.y / M_PI;
		v -= floor(v);

		int i_u = (int)((float)(TEXTURE_HEIGHT) * u);
		int i_v = (int)((float)(TEXTURE_WIDTH) * v);

		i_u = (int)((float)(i_u + obj.texture.dy) / obj.texture.scale) % TEXTURE_HEIGHT;
		i_v = (int)((float)(i_v + obj.texture.dx) / obj.texture.scale) % TEXTURE_WIDTH;

		return (choose_procedural_texture(noise, obj.proc_tex, i_u, i_v, obj.texture));
}

t_vec3 procedural_texture(t_object obj, t_vec3 point, __global t_vec3 *noise)
{
	if (obj.type == 0)
		return (procedural_texture_sphere(noise, obj, point));
	if (obj.type == 1)
		return (procedural_texture_plane(noise, obj, point));
	if (obj.type == 2)
		return (procedural_texture_cone(noise, obj, point));
	if (obj.type == 3)
		return (procedural_texture_cylinder(noise, obj, point));
	return (vec3_init(0, 0, 0));
}
