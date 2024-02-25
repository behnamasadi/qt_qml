# HTTP Request Methods
request methods to indicate the desired action to be performed for a given
resource

## GET
The GET method requests for a specified resource (only to retrieve data).
When using GET, data parameters are included in the URL and visible to everyone.
However, when using POST, data is not displayed in the URL but in the HTTP
message body. GET is less secure because the URL contains part of the data sent.
On the other hand, POST is safer because the parameters are not stored in web
server logs or the browser history. GET requests can be cached and remain in the
browser history, while POST requests cannot.


### HEAD
The HEAD method asks for a response identical to a GET request, but without the
response body.

## POST
The POST method submits an entity, often causing a change in state or side
effects on the server. The POST method sends data through the HTTP message body,
(unlike GET has no limitation).

A POST request is typically sent via:
- HTML form
- XMLHttpRequest

In POST request, you have to encode the data that forms the body of the request.
The type of the body of the request is indicated by the Content-Type header

All the possible values for HTTP header "Content-Type":

### Content-Type

1. application/*
For instance  application/json,  application/x-www-form-urlencoded,
application/xhtml+xml

1.1. application/x-www-form-urlencoded: values are encoded in key-value tuples
separated by '&', with a '='. Non-alphanumeric characters encoded

2. multipart/*
For instance multipart/mixed,  multipart/alternative   multipart/related
multipart/form-data 2.1. multipart/form-data suitable to use with binary data

3. text/*
for instance text/css, text/plain


4. audio/*

5. video/*

Refs: [1](https://stackoverflow.com/questions/23714383/what-are-all-the-possible-values-for-http-content-type-header,), [2](https://www.iana.org/assignments/media-types/media-types.xhtml)


## PUT
The PUT method replaces all current representations of the target resource with
the request payload.

## DELETE
The DELETE method deletes the specified resource.

## CONNECT
The CONNECT method establishes a tunnel to the server identified by the target
resource.

## OPTIONS
The OPTIONS method describes the communication options for the target resource.

## TRACE
The TRACE method performs a message loop-back test along the path to the target
resource.

## PATCH
The PATCH method applies partial modifications to a resource.


# QNetworkAccessManager
# QNetworkRequest
# QNetworkReply



## QNetworkReply  Best Practices
Refs: [1](https://forum.qt.io/topic/37692/solved-qnetworkreply-best-practices)

# QHttpMultiPart

## Boundary in multipart/form-data
Refs: [1](https://stackoverflow.com/questions/3508338/what-is-the-boundary-in-multipart-form-data)


[source](../src/network.cpp)

Refs: [1](https://doc.qt.io/qt-6/qhttpmultipart.html)
# Network Examples

Refs: [1](https://doc.qt.io/qt-6/examples-network.html)

