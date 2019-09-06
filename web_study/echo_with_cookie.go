package main

import (
	"fmt"
	"log"
	"net/http"
	"net/http/httputil"
)

func handler(w http.ResponseWriter, r *http.Request) {

	w.Header().Add("Set-Cookie", "VISIT=TRUE")

	if _, ok := r.Header["Cookie"]; ok {
		fmt.Fprintf(w, "<html><body> Already Visited </body></html>\n")
	}else{
		fmt.Fprintf(w, "<html><body> First Visit </body></html>\n")
	}

	dump, err := httputil.DumpRequest(r, true)

	if err != nil {
		http.Error(w, fmt.Sprint(err), http.StatusInternalServerError)
		return
	}

	fmt.Println(string(dump))
	fmt.Fprint(w, "<html><body>hello</body></html>\n")
}

func main() {
	var httpServer http.Server
	http.HandleFunc("/", handler)
	log.Println("start http listening:18888")
	httpServer.Addr = ":18888"
	log.Println(httpServer.ListenAndServe())
}
