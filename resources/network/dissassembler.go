package main

import (
	"io/ioutil"
	"math"
	"os"
	"strconv"
)

func main() {
	file, _ := os.Open("./bigfile.mkv")
	const chunkSize = 1 << 25
	fileInfo, _ := file.Stat()
	var fileSize int64 = fileInfo.Size()
	numOfParts := uint64(math.Ceil(float64(fileSize) / float64(chunkSize)))
	for i := uint64(0); i < numOfParts; i++ {
		bufferSize := int(math.Min(float64(chunkSize), float64(fileSize-int64(chunkSize*i))))
		buffer := make([]byte, bufferSize)
		_, _ = file.Read(buffer)
		bufferName := "bigfile_part" + strconv.FormatUint(i+1, 10)

		_, _ = os.Create(bufferName)

		_ = ioutil.WriteFile(bufferName, buffer, os.ModeAppend)
	}
}
