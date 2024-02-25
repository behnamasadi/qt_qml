# JSON

JSON, which stands for JavaScript Object Notation, is a lightweight data interchange format. It's easy for humans to read and write and easy for machines to parse and generate. JSON is often used for transmitting data in web applications (e.g., sending data from a server to a client, so it can be displayed on a webpage, or vice versa).

Here are the key features and structure of JSON:

1. **Format:**
   - JSON is text written in a JavaScript object-like syntax.
   - It can be used with many programming languages, not just JavaScript.

2. **Data Types:**
   - JSON supports the following data types:
     - **Numbers:** Double-precision floating-point format, similar to JavaScript's numbers.
     - **Strings:** A sequence of zero or more Unicode characters. Strings are wrapped in double quotes.
     - **Booleans:** True or false values.
     - **Null:** An empty value, written as `null`.
     - **Arrays:** An ordered list of values, enclosed in square brackets (e.g., `[1, 2, 3]`). Arrays in JSON can contain items of different types, including numbers, strings, booleans, objects, arrays, etc.
     - **Objects:** An unordered collection of key-value pairs, enclosed in curly braces (e.g., `{"name": "John", "age": 30}`). Each key is a string followed by a colon, and key-value pairs are separated by commas.

3. **Syntax Rules:**
   - Objects are wrapped in curly braces `{}`.
   - Arrays are wrapped in square brackets `[]`.
   - Keys must be strings and are written in double quotes.
   - Values can be strings, numbers, objects, arrays, booleans, or null.
   - Key-value pairs in objects are separated by commas.
   - Array elements are also separated by commas.

4. **Use Cases:**
   - JSON is often used for serializing and transmitting structured data over a network connection, especially between a server and web applications.
   - It's commonly used for APIs and web services, where applications need to exchange data.

5. **Example:**

   ```json
   {
       "name": "John Doe",
       "age": 30,
       "isMarried": false,
       "children": ["Alice", "Bob"],
       "address": {
           "street": "123 Main St",
           "city": "Anytown",
           "zipCode": "12345"
       }
   }
   ```
# JSON in Qt

This JSON object represents a person with various properties, including an array of children's names and a nested object representing an address.

6. **Readability and Compatibility:**
   - JSON is easy to read and write for humans, and easy to parse and generate for machines.
   - It's language-independent, making it a popular choice for data interchange.


Here's an overview of the primary Qt classes for JSON handling:

1. **QJsonDocument:**
   - This class represents a JSON document in a Qt application. 
   - It can be used to parse JSON data from a string or load it from a file, and can also be used to serialize (convert to JSON format) Qt data structures.
   - `QJsonDocument` can contain either a `QJsonObject` or a `QJsonArray` as its root element.

2. **QJsonObject:**
   - This class represents a JSON object, which is essentially a collection of key-value pairs where keys are strings, and values can be various JSON types (e.g., strings, numbers, objects, arrays).
   - `QJsonObject` provides functions to insert, remove, and access values using keys. It also allows iteration over key-value pairs.

3. **QJsonArray:**
   - As the name suggests, this class represents a JSON array, which is an ordered collection of JSON values.
   - `QJsonArray` offers functions to append, remove, and access elements in the array. Like `QJsonObject`, it also supports iteration.

4. **QJsonValue:**
   - This class represents a value in JSON, which could be a string, a number, an object, an array, a boolean, or null.
   - `QJsonValue` has functions to check the type of the value and to retrieve the value in a suitable format (e.g., as a `QString`, `QJsonObject`, `QJsonArray`, etc.).

5. **QJsonParseError:**
   - This class is used in conjunction with `QJsonDocument` to report errors that occurred during parsing of JSON data.
   - It contains details about the error, including the error type and the offset in the input JSON data where the error occurred.

### Working with JSON in Qt

Here's a simple example to demonstrate how these classes can be used:

```cpp

    // Create a JSON object
    QJsonObject jsonObj;
    jsonObj["name"] = "John Doe";
    jsonObj["age"] = 30;
    jsonObj["isMarried"] = false;

    // Create a JSON array and add it to the object
    QJsonArray jsonArr;
    jsonArr.append("Alice");
    jsonArr.append("Bob");
    jsonObj["children"] = jsonArr;

    // Convert the JSON object to a document
    QJsonDocument jsonDoc(jsonObj);

    // Serialize the document to a JSON string
    QString jsonString = jsonDoc.toJson();
    std::cout << jsonString.toStdString() << std::endl;

    // Parse a JSON string to a document
    QJsonParseError parseError;
    QJsonDocument doc2 = QJsonDocument::fromJson(jsonString.toUtf8(), &parseError);

    // Check for errors during parsing
    if (parseError.error != QJsonParseError::NoError) {
        std::cerr << "Error parsing JSON: " << parseError.errorString().toStdString() << std::endl;
        return -1;
    }

    // Extract data from the parsed document
    QJsonObject obj = doc2.object();
    if (obj.contains("name") && obj["name"].isString()) {
        std::cout << "Name: " << obj["name"].toString().toStdString() << std::endl;
    }


}
```

# QJson Iterators


To iterate over a `QJsonDocument` or `QJsonObject` in Qt, you need to first understand the structure of your JSON data. Let's consider the earlier JSON example:

```json
{
    "name": "John Doe",
    "age": 30,
    "isMarried": false,
    "children": ["Alice", "Bob"],
    "address": {
        "street": "123 Main St",
        "city": "Anytown",
        "zipCode": "12345"
    }
}
```

### Iterating over a `QJsonObject`

If this JSON is stored in a `QJsonObject`, you can iterate over it like this:

```cpp
QJsonObject jsonObject = /* your JSON object */;
for (auto it = jsonObject.begin(); it != jsonObject.end(); ++it) {
    QString key = it.key();
    QJsonValue value = it.value();

    // Process key and value
    qDebug() << "Key:" << key << ", Value:" << value;
}
```

This loop will iterate over each key-value pair in the `QJsonObject`. If the value is another JSON object or an array, you can further process it depending on your requirements.

### Iterating over a `QJsonArray`

If you have a `QJsonArray` (like the "children" array in the example), you can iterate over it like this:

```cpp
QJsonArray jsonArray = /* your JSON array */;
for (auto value : jsonArray) {
    // Process each value in the array
    qDebug() << "Array item:" << value;
}
```

### Iterating over a `QJsonDocument`

A `QJsonDocument` can hold either a `QJsonObject` or a `QJsonArray`. To iterate over a `QJsonDocument`, you first need to extract the object or array it contains:

```cpp
QJsonDocument jsonDoc = /* your JSON document */;

// Check if the document contains an object
if (jsonDoc.isObject()) {
    QJsonObject jsonObj = jsonDoc.object();
    // Iterate over the object as shown above
}

// Check if the document contains an array
if (jsonDoc.isArray()) {
    QJsonArray jsonArr = jsonDoc.array();
    // Iterate over the array as shown above
}
```

### Notes

- When you encounter nested objects or arrays, you can recursively apply these methods to iterate over their contents.
- Remember to check the type of each `QJsonValue` before processing it (e.g., whether it's an object, array, string, etc.) to handle it appropriately.
- Iterating over JSON structures is often part of a larger data processing task, so consider the context of what you need to achieve with the data when writing your iteration logic.




To iterate over a `QJsonObject` or `QJsonDocument` in a memory-efficient way and avoid unnecessary copying, you can use the following approaches:

### For `QJsonObject`:

When iterating over a `QJsonObject`, use references to avoid copying the keys and values. The iterator provides direct access to the key and value:

```cpp
QJsonObject jsonObject = /* your JSON object */;
for (auto it = jsonObject.constBegin(); it != jsonObject.constEnd(); ++it) {
    const QString& key = it.key();
    const QJsonValue& value = it.value();

    // Process key and value
    // ...
}
```

By using `constBegin()` and `constEnd()` along with references (`const QString&` and `const QJsonValue&`), you ensure that the elements are accessed without making a copy.

### For `QJsonArray`:

Similarly, when iterating over a `QJsonArray`, use a reference in the loop to avoid copying each element:

```cpp
QJsonArray jsonArray = /* your JSON array */;
for (const QJsonValue& value : jsonArray) {
    // Process each value in the array
    // ...
}
```

This approach ensures that the values in the array are accessed by reference.

### For `QJsonDocument`:

For a `QJsonDocument`, first determine whether it contains an object or an array, and then iterate over it using the appropriate method as described above:

```cpp
QJsonDocument jsonDoc = /* your JSON document */;

if (jsonDoc.isObject()) {
    QJsonObject jsonObj = jsonDoc.object();
    // Use the QJsonObject iteration method
}

if (jsonDoc.isArray()) {
    QJsonArray jsonArr = jsonDoc.array();
    // Use the QJsonArray iteration method
}
```

### Notes:

- Remember that `QJsonValue` itself can represent different types (e.g., object, array, string, number). Use its methods like `isObject()`, `isArray()`, etc., to determine the type and handle it accordingly.
- For very large JSON structures, consider the overall memory usage of the structure itself. In some cases, if the JSON is too large, you might need to think about alternative data handling strategies that do not involve loading the entire structure into memory at once.
- The above methods are efficient in terms of avoiding unnecessary copies during iteration but keep in mind that the original JSON parsing step (when creating `QJsonDocument` or `QJsonObject`) also has memory implications.



[source](../src/json_example.cpp)



Refs: [1](https://doc.qt.io/qt-6/json.html)
