package main

type Ray struct {
	Origin    Vector3
	Direction Vector3
}

type RayHit struct {
	Point     Vector3
	Normal    Vector3
	T         float64
	FrontFace bool
}

func NewRay(origin, direction Vector3) Ray {
	return Ray{origin, direction}
}

func (r *Ray) At(t float64) Vector3 {
	v := r.Direction.Mul(t)
	return v.Add(r.Origin)
}

func (r *Ray) CalcColor(shapes ShapeList, depth int) Vector3 {
	// TODO
	return NewVector3(0, 0, 0)
}

func (h *RayHit) SetFaceNormal(r *Ray, normal *Vector3) {
	h.FrontFace = r.Direction.Dot(*normal) < 0;

	if (h.FrontFace) {
		h.Normal = normal.Neg()
	} else {
		h.Normal = *normal
	}
}
