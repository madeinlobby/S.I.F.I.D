package main

import (
	"io/ioutil"
	"math"
	"net/http"
	"os"
	"strconv"
)

type miniServer struct {
	partNumber   int
	mainFileName string
	chunk        []byte
}

var requestCounter = 11

type mainServer int

func (m miniServer) ServeHTTP(res http.ResponseWriter, req *http.Request) {
	//compress the chunk and then feed it to mini client
	fileToCompress, _ := os.Create(m.mainFileName + "part" + string(m.partNumber))
	_ = ioutil.WriteFile(fileToCompress.Name(), m.chunk, os.ModeAppend)
	//compress here

	//send compressed chunk here

	//delete here

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
	_, _ = res.Write([]byte("port:" + strconv.FormatInt(int64(requestCounter*100), 10) + "parts:" + strconv.FormatInt(int64(numOfParts), 10)))
	//client will repeatedly try to connect to port rC*100 + i for i th file part
	for i := 0; i < numOfParts; i++ {
		var newMiniServer miniServer
		newMiniServer.mainFileName = fileName
		bufferSize := int(math.Min(float64(chunkSize), float64(fileSize-int64(chunkSize*i))))
		buffer := make([]byte, bufferSize)
		_, _ = file.Read(buffer)
		newMiniServer.partNumber = i
		newMiniServer.chunk = buffer
		_ = http.ListenAndServe(":"+strconv.FormatInt(int64(requestCounter*100+i), 10), newMiniServer)
	}
	requestCounter++
	if requestCounter == 80 {
		requestCounter = 11
	}
}

func main() {

}
