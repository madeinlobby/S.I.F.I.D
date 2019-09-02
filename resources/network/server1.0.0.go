package main

import (
	"io"
	"net/http"
	"os"
)

type hello float64

func (h hello) ServeHTTP(res http.ResponseWriter, req *http.Request) {
	filename := req.URL.Query().Get("file")
	file, _ := os.Open(filename)
	_, _ = io.Copy(res, file)

}

func main() {
	var h hello
	http.ListenAndServe(":6070", h)

}
