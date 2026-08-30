#include <stdio.h>
#include <tgmath.h>

double max_norm(const double *vector, const int size, const char op1, const int op2, const int square)
{
    double max = -1;

    switch (op1)
    {
        case '1':
        {
            if (square == 0) goto def;

            for (int i = op2 * size - 1; i < size; i++)
            {
                double _ = fabs(vector[i]);
                if (_ > max)
                {
                    max = _;
                }
            }
        }
        break;

        case '2':
        {
            if (square == 0) return fabs(vector[op2 - 1]);

            for (int i = 0; i < size; i++)
            {
                double _ = fabs(vector[i * size + (op2 - 1)]);
                if (_ > max)
                {
                    max = _;
                }
            }
        }
        break;

        case '3':
        {
            if (square == 0) return fabs(vector[0]);

            for (int i = 0; i < size; i++)
            {
                double _ = fabs(vector[i * size + i]);
                if (_ > max)
                {
                    max = _;
                }
            }
        }
        break;

        case '4':
        {
            if (square == 0)
            {
                for (int i = 0; i < size; i++)
                {
                    double _ = fabs(vector[i]);
                    if (_ > max && vector[i] > 0)
                    {
                        max = _;
                    }
                }

                goto end;
            }

            for (int i = 0; i < size * size; i++)
            {
                if (vector[i] > 0)
                {
                    double _ = fabs(vector[i]);
                    if (_ > max)
                    {
                        max = _;
                    }
                }
            }
        }
        break;

        case '5':
        {
            if (square == 0)
            {
                for (int i = 1; i < size; i++)
                {
                    double _ = fabs(vector[i]);
                    if (_ > max)
                    {
                        max = _;
                    }
                }

                goto end;
            }

            for (int i = 0; i < size; i++)
            {
                for (int j = i + 1; j < size; j++)
                {
                    double _ = fabs(vector[i * size + j]);
                    if (_ > max)
                    {
                        max = _;
                    }
                }
            }
        }
        break;

        default:
        {
        def:
            for (int i = 0; i < size; i++)
            {
                double _ = fabs(vector[i]);
                if (_ > max)
                {
                    max = _;
                }
            }
        }
    }

end:
    return max;
}
