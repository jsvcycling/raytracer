package main

type Camera struct {
	Origin Vector3
	LowerLeftCorner Vector3
	Horizontal Vector3
	Vertical Vector3
}

func NewCamera() *Camera {
	aspectRatio := float64(16.0 / 9.0)
	viewportHeight := 2.0
	viewportWidth := aspectRatio * viewportHeight
	focalLength := 1.0

	camera := new(Camera)
	camera.Origin = NewVector3(0, 0, 0)
	camera.Horizontal = NewVector3(viewportWidth, 0, 0)
	camera.Vertical = NewVector3(0, viewportHeight, 0)

	camera.LowerLeftCorner = camera.calcLowerLeftCorner(focalLength)

	return camera
}

func (c *Camera) GetRay(u, v float64) *Ray {
	return &Ray {
		Origin: c.Origin,
		Direction: c.calcRayDir(u, v),
	}
}

func (c *Camera) calcRayDir(u, v float64) Vector3 {
	temp_h := c.Horizontal.Mul(u)
	temp_v := c.Vertical.Mul(v)
	return c.LowerLeftCorner.Add(temp_h).Add(temp_v).Sub(c.Origin)
}

func (c *Camera) calcLowerLeftCorner(focalLength float64) Vector3 {
	temp_h := c.Horizontal.Mul(0.5)
	temp_v := c.Vertical.Mul(0.5)
	focal := NewVector3(0, 0, focalLength)
	return c.Origin.Sub(temp_h).Sub(temp_v).Sub(focal)
}
