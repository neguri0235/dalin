package main

import (
	"log"
	"net/http"
	"os"
	"strings"
)

func main() {
	file, err := os.Open("client.go")
	resp, err := http.Post("http://localhost:18888", "text/plain", file)
	if err != nil {
		panic(err)
	}
	log.Println("Status:", resp.Status)
	log.Println("---- 텍스트 전송------")
	reader := strings.NewReader("테스트 텍스트")
	resp, err = http.Post("http://localhost:18888", "text/plain", reader)

	if err != nil {
		panic(err)
	}
	log.Println("Status:", resp.Status)
}
