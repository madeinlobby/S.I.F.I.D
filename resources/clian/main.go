package main

import (
	"io"
	"net/http"
	"os"
)

func main() {
	resp, _ := http.Get("http://localhost:6070/?file=pic.jpg")
	out, _ := os.Create("new.jpg")
	_, _ = io.Copy(out, resp.Body)
}
