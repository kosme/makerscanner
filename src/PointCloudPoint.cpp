/*
* Copyright 2009-2010, Andrew Barry
*
* This file is part of MakerScanner.
*
* MakerScanner is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License (Version 2, June 1991) as published by
* the Free Software Foundation.
*
* MakerScanner is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "PointCloudPoint.h"

// copy constructor
PointCloudPoint::PointCloudPoint(PointCloudPoint *point)
{
	dist = point->dist;
	theta = point->theta;
	phi = point->phi;

	r = point->r;
	g = point->g;
	b = point->b;
	w = point->w;
	h = point->h;
	laserPosition = point->laserPosition;
}

// Generates the point cloud string for this point (one line)
wxString PointCloudPoint::GetPlyString()
{

	double pxDist = dist;


	double x, y, z;

	x = pxDist * tan(theta);
	y = pxDist;
	z = pxDist * tan(phi);

	wxString xString = "";
	xString << x;

	wxString yString = "";
	yString << y;

	wxString zString = "";
	zString << z;

	wxString rString = "";
	rString << r;

	wxString gString = "";
	gString << g;

	wxString bString = "";
	bString << b;

	return xString + " " + yString + " " + zString + " " + rString + " "
		+ gString + " " + bString;

}
