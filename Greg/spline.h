#ifndef _SPLINE_H
#define _SPLINE_H

#define SPLINE_MAX_POINTS 16

class Spline
{
    public:
        Spline();

        /**
         * Add a point (x, y) to the spline
         */
        void addPoint(double x, double y);

        /**
         * Gets the xMax of the spline
         */
        double getXMax();

        /**
         * Get the value for the given x
         */
        double get(double x);

        /**
         * Gets the value for the given x, modulo the size of the spline
         */
        double getMod(double x);

    protected:
        /**
         * Spline points
         */
        double points[SPLINE_MAX_POINTS][2];

        /**
         * Number of points
         */
        int nbPoints;

        /**
         * The nth item of this array is the slope between the nth point and the
         * n+1th point
         */
        double ds[SPLINE_MAX_POINTS-1];
};

#endif
