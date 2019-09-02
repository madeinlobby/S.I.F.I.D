package main

import (
	"fmt"
	"os"
	"strconv"
)

func main() {
	newF, _ := os.Create("./reassembled.mkv")
	for i := 0; true; i++ {
		file, err := os.Open("./parts/bigfile_part" + strconv.FormatUint(uint64(i+1), 10))
		if err != nil {
			fmt.Println("Did " + strconv.FormatUint(uint64(i), 10) + " parts!")
			break
		}
		fmt.Println("opened" + "./parts/bigfile_part" + strconv.FormatUint(uint64(i+1), 10))
		fileS, _ := file.Stat()
		fileSize := uint64(fileS.Size())
		bytes := make([]byte, fileSize)
		_, _ = file.Read(bytes)
		_, _ = newF.WriteString(string(bytes))
	}
	_ = newF.Close()

}
