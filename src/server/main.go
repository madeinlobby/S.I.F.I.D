package main

import (
	"net/http"
	"os"
)

type miniServer int

type mainServer int

func (m miniServer) init(fileName string, partNumber int) {
	//compress the chunk and then feed it to mini client
}

func (m mainServer) ServeHTTP(res http.ResponseWriter, req *http.Request) {
	fileName := req.URL.Query().Get("file")
	file, err := os.Open(fileName)
	if err != nil {
		_, _ = res.Write([]byte("Error 404! File not found!"))
		return
	}
	//cut file into chunks here then make miniServers for each chunk

}

func main() {

}
