package main

import (
	"io/ioutil"
	"log"
	"net/http"
	"net/url"
)

func main() {

	values := url.Values{
		"query": {"hello world"},
	}

	resp, err := http.Get("http://localhost:18888" + "?" + values.Encode())

	if err != nil {
		panic(err)
	}

	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)

	if err != nil {
		panic(err)
	}
	log.Println("Headers:", resp.Header)
	log.Println(string(body))
	log.Println("status:", resp.Status)
	log.Println("statusCode:", resp.StatusCode)
	log.Println("Content-Length:", resp.Header.Get("Content-Length"))

	log.Println("-------------------------")

	resp, err = http.Head("http://localhost:18888")

	if err != nil {
		panic(err)
	}

	log.Println("Status:", resp.Status)
	log.Println("Headers:", resp.Header)
}
