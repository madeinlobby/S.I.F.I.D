package main

import "net/http"

type mainServer int

func (m mainServer) ServeHTTP(res http.ResponseWriter, req *http.Request) {

}

func main() {

}
