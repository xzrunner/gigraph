/**********************************************************************
Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
********************************************************************/

#include <RadeonRays/bbox.h>

namespace
{

sm::vec3 Min(const sm::vec3& a, const sm::vec3& b)
{
    sm::vec3 out;
    out.x = std::min(a.x, b.x);
    out.y = std::min(a.y, b.y);
    out.z = std::min(a.z, b.z);
    return out;
};

sm::vec3 Max(const sm::vec3& a, const sm::vec3& b)
{
    sm::vec3 out;
    out.x = std::max(a.x, b.x);
    out.y = std::max(a.y, b.y);
    out.z = std::max(a.z, b.z);
    return out;
};

}

namespace RadeonRays
{

bbox::bbox(sm::vec3 const& p1, sm::vec3 const& p2)
    : pmin(Min(p1, p2))
    , pmax(Max(p1, p2))
{
}

sm::vec3 bbox::center()  const { return (pmax + pmin) * 0.5f; }
sm::vec3 bbox::extents() const { return pmax - pmin; }

float bbox::surface_area() const
{
	sm::vec3 ext = extents();
	return 2.f * (ext.x * ext.y + ext.x * ext.z + ext.y * ext.z);
}

// Grow the bounding box by a point
void bbox::grow(sm::vec3 const& p)
{
	pmin = Min(pmin, p);
	pmax = Max(pmax, p);
}
// Grow the bounding box by a box
void bbox::grow(bbox const& b)
{
	pmin = Min(pmin, b.pmin);
	pmax = Max(pmax, b.pmax);
}

bool bbox::contains(sm::vec3 const& p) const
{
	sm::vec3 radius = extents() * 0.5f;
	return std::abs(center().x - p.x) <= radius.x &&
		fabs(center().y - p.y) <= radius.y &&
		fabs(center().z - p.z) <= radius.z;
}

bbox bboxunion(bbox const& box1, bbox const& box2)
{
	bbox res;
	res.pmin = Min(box1.pmin, box2.pmin);
	res.pmax = Max(box1.pmax, box2.pmax);
	return res;
}

bbox intersection(bbox const& box1, bbox const& box2)
{
	return bbox(Max(box1.pmin, box2.pmin), Min(box1.pmax, box2.pmax));
}

void intersection(bbox const& box1, bbox const& box2, bbox& box)
{
	box.pmin = Max(box1.pmin, box2.pmin);
	box.pmax = Min(box1.pmax, box2.pmax);
}

#define BBOX_INTERSECTION_EPS 0.f

bool intersects(bbox const& box1, bbox const& box2)
{
	sm::vec3 b1c = box1.center();
	sm::vec3 b1r = box1.extents() * 0.5f;
	sm::vec3 b2c = box2.center();
	sm::vec3 b2r = box2.extents() * 0.5f;

	return (fabs(b2c.x - b1c.x) - (b1r.x + b2r.x)) <= BBOX_INTERSECTION_EPS &&
		(fabs(b2c.y - b1c.y) - (b1r.y + b2r.y)) <= BBOX_INTERSECTION_EPS &&
		(fabs(b2c.z - b1c.z) - (b1r.z + b2r.z)) <= BBOX_INTERSECTION_EPS;
}

bool contains(bbox const& box1, bbox const& box2)
{
	return box1.contains(box2.pmin) && box1.contains(box2.pmax);
}
	
}
