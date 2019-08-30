var url = require('url');

var urlStr = 'https://search.naver.com/search.naver?sm=top_hty&fbm=1&ie=utf8&query=node.js';

var curUrl = url.parse(urlStr);

console.dir(curUrl)
console.log('query -> ' + curUrl.query);
/*
Url {
  protocol: 'https:',
  slashes: true,
  auth: null,
  host: 'search.naver.com',
  port: null,
  hostname: 'search.naver.com',
  hash: null,
  search: '?sm=top_hty&fbm=1&ie=utf8&query=node.js',
  query: 'sm=top_hty&fbm=1&ie=utf8&query=node.js',
  pathname: '/search.naver',
  path: '/search.naver?sm=top_hty&fbm=1&ie=utf8&query=node.js',
  href: 'https://search.naver.com/search.naver?sm=top_hty&fbm=1&ie=utf8&query=no
de.js' }

*/

var curStr = url.format(curUrl);
console.log('url -> ' + curStr);
/*
url -> https://search.naver.com/search.naver?sm=top_hty&fbm=1&ie=utf8&query=node.js
*/

var queryString = require('querystring');
var params = queryString.parse(curUrl.query);
console.log('검색어 : ' + params.query);
/*
검색어 : node.js
*/