package main

import (
	"fmt"
	"io"
	"math"
)

func WriteColor(writer io.Writer, color Vector3, samplesPerPixel int) {
	scale := 1.0 / float64(samplesPerPixel)

	// Gamma correction
	r := math.Sqrt(scale * color.X)
	g := math.Sqrt(scale * color.Y)
	b := math.Sqrt(scale * color.Z)

	r = Clamp(r, 0, 0.999) * 256
	g = Clamp(g, 0, 0.999) * 256
	b = Clamp(b, 0, 0.999) * 256

	text := fmt.Sprintf("")
	writer.Write([]byte(text))
}
