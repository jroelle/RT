
double triangle_square(double a, double b, double c)
{
	double p;

	p = (a + b + c) / 2.0;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}

double inside_triangle(t_vec3 p, t_vec3 a, t_vec3 b, t_vec3 c)
{
	int inside;
	double AB;
	double BC;
	double CA;
	double AP;
	double BP;
	double CP;
	double diff;

	inside = 0;
	AB = sqrt((a.x - b.x) * (a.x - b.x) +
			  (a.y - b.y) * (a.y - b.y) +
			  (a.z - b.z) * (a.z - b.z));
	BC = sqrt((b.x - c.x) * (b.x - c.x) +
			  (b.y - c.y) * (b.y - c.y) +
			  (b.z - c.z) * (b.z - c.z));
	CA = sqrt((a.x - c.x) * (a.x - c.x) +
			  (a.y - c.y) * (a.y - c.y) +
			  (a.z - c.z) * (a.z - c.z));

	AP = sqrt((p.x - a.x) * (p.x - a.x) +
			  (p.y - a.y) * (p.y - a.y) +
			  (p.z - a.z) * (p.z - a.z));
	BP = sqrt((p.x - b.x) * (p.x - b.x) +
			  (p.y - b.y) * (p.y - b.y) +
			  (p.z - b.z) * (p.z - b.z));
	CP = sqrt((p.x - c.x) * (p.x - c.x) +
			  (p.y - c.y) * (p.y - c.y) +
			  (p.z - c.z) * (p.z - c.z));
	diff = (triangle_square(AP, BP, AB) +
			triangle_square(AP, CP, CA) +
			triangle_square(BP, CP, BC)) -
		   triangle_square(AB, BC, CA);
	if (fabs(diff) < 1e-10)
		inside = 1;
	return inside;
}

double reflection_coefficient(t_vec3 ray, t_vec3 normal, double n1, double n2)
{
	double cosa = vec3_dot(vec3_mul_n(ray, -1), normal);
	double r0 = pow((n1 - n2) / (n1 + n2), 2.0);
	return (r0 + (1.0 - r0) * pow(1.0 - cosa, 2.0));
}
