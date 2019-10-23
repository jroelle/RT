int	quadratic_solution_torus(double k[3], double dis[2])
{
    double p, q, D;

    p = k[1] / (2.0 * k[2]);
    q = k[0] / k[2];
    D = p * p - q;
    if (fabs(D) < 0.000001)
    {
	    dis[0] = -p;
	    return 1;
    }
    else if (D < 0)
    {
	    return 0;
    }
    else /* if (D > 0) */
    {
	    double sqrt_D = sqrt(D);

	    dis[0] = sqrt_D - p;
	    dis[1] = -sqrt_D - p;
        return 2;
    }
}

int	quadratic_solution(double k[3], double dis[4])
{
    double p, q, D;

    p = k[1] / (2.0 * k[2]);
    q = k[0] / k[2];
    D = p * p - q;
    D = k[1] * k[1] - 4.0 * k[0] * k[2];
    if (fabs(D) < 0.000001)
    {
	    dis[0] = -k[1] / (2.0 * k[0]);
	    return 1;
    }
    else if (D < 0)
    {
	    return 0;
    }
    else /* if (D > 0) */
    {
	    double sqrt_D = sqrt(D);

	    dis[0] = (-k[1] - sqrt_D) / (2.0 * k[0]);
	    dis[1] = (-k[1] + sqrt_D) / (2.0 * k[0]);
        p = dis[0];
        q = dis[1];
        dis[0] = p < q ? p : q;
        dis[1] = p < q ? q : p;
        return 2;
    }
}

int cubic_solution(double k[4], double dis[4])
{
    int i, num;
    double sub, a, b, c, a2, p, q, p3, d, phi;

	a = k[2] / k[3];
	b = k[1] / k[3];
	c = k[0] / k[3];

	a2 = a * a;
	p = 1.0 / 3.0 * (-1.0 / 3.0 * a2 + b);
	q = 1.0 / 2.0 * (2.0 / 27.0 * a * a2 - 1.0 / 3.0 * a * b + c);

	p3 = p * p * p;
	d = q * q + p3;

	if (fabs(d) < 0.000001)
	{
		if (fabs(q) < 0.000001)
		{
			dis[0] = 0;
			num = 1;
		}
		else
		{
			dis[1] = -cbrt(-q);
			dis[0] = -2.0 * dis[1];
			num = 2;
		}
	}
	else if (d < 0)
	{
		phi = 1.0 / 3.0 * acos(-q / sqrt(-p3));
		dis[0] = 2.0 * sqrt(-p) * cos(phi);
		dis[1] = -2.0 * sqrt(-p) * cos(phi + M_PI / 3.0);
		dis[2] = -2.0 * sqrt(-p) * cos(phi - M_PI / 3.0);
		num = 3;
	}
	else
	{
		dis[0] = cbrt(sqrt(d) - q) - cbrt(sqrt(d) + q);
		num = 1;
    }
    sub = 1.0 / 3.0 * a;
    i = 0;
    while (i < num)
    {
        dis[i] -= sub;
        i++;
    }
    return (num);
}

void quartic_solution(double coef[5], double dis[4])
{
    double a;
    double b;
    double c;
    double d;
    double z, u, v, sub, sq_a, p, q, r;
    int i, num;
    double k[4];

    a = coef[3] / coef[4];
    b = coef[2] / coef[4];
    c = coef[1] / coef[4];
    d = coef[0] / coef[4];

    sq_a = a * a;
    p = -3.0 / 8.0 * sq_a + b;
    q = 1.0 / 8.0 * sq_a * a - 1.0 / 2.0 * a * b + c;
    r = -3.0 / 256.0 * sq_a * sq_a + 1.0 / 16.0 * sq_a * b - 1.0 / 4.0 * a * c + d;

    if (fabs(r) < 0.00001)
    {
        k[0] = q;
        k[1] = p;
        k[2] = 0.0;
        k[3] = 1.0;
        num = cubic_solution(k, dis);
        dis[num++] = 0.0;
    }
    else
    {
        k[0] = 1.0 / 2.0 * r * p - 1.0 / 8.0 * q * q;
        k[1] = -r;
        k[2] = -1.0 / 2.0 * p;
        k[3] = 1.0;

        cubic_solution(k, dis);
        z = dis[0];
        u = z * z - r;
        v = 2.0 * z - p;

        if (fabs(u) < 0.000001)
            u = 0;
        else if (u > 0)
            u = sqrt(u);
        else
            return ;

        if (fabs(v) < 0.000001)
            v = 0;
        else if (v > 0)
            v = sqrt(v);
        else
            return ;
        k[0] = z - u;
        k[1] = q < 0 ? -v : v;
        k[2] = 1.0;
        i = 0;
        while (i < 4)
        {
            dis[i] = INFINITY;
            i++;
        }
        quadratic_solution_torus(k, dis + 2);

        k[0] = z + u;
        k[1] = q < 0 ? v : -v;
        k[2] = 1.0;
        quadratic_solution_torus(k, dis);
    }
    sub = 1.0 / 4.0 * a;
    i = 0;
    while (i < 4)
    {
        if (dis[i] != -1.0)
            dis[i] -= sub;
        i++;
    }
}