package main

import (
	"math"
	"net/http"
	"os"
)

type miniServer int

var requestCounter = 11

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
	const chunkSize = 1 << 25
	fileInfo, _ := file.Stat()
	var fileSize int64 = fileInfo.Size()
	numOfParts := int(math.Ceil(float64(fileSize) / float64(chunkSize)))
	_, _ = res.Write([]byte("port:" + string(requestCounter*100) + "parts:" + string(numOfParts)))

	for i := 0; i < numOfParts; i++ {
		var newMiniServer miniServer
		go newMiniServer.init(fileName, i)
	}
	requestCounter++
	if requestCounter == 80 {
		requestCounter = 11
	}
}

func main() {

}
