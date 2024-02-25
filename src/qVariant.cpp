#include <QByteArray>
#include <QColor>
#include <QDate>
#include <QMetaType>
#include <QVariant>

int main(int argc, char **argv) {
  // Type Flexibility:
  {
    QVariant variant;
    variant = 42;               // Storing an integer
    variant = QString("Hello"); // Storing a string
    variant = QColor(Qt::red);  // Storing a QColor
  }
  // Implicit Conversion:
  {
    QVariant variant = 42;
    int intValue = variant.toInt(); // Implicit conversion from QVariant to int

    QVariant variant2 = "123";
    QString strValue =
        variant2.toString(); // Implicit conversion from QVariant to QString
  }

  // Type Querying:
  {
    QVariant variant = 3.14;
    //        QMetaType::Type type = variant.type(); // Get the type of the
    //        stored value

    //        if (type == QMetaType::Double) {
    //            // Handle double value
    //        }
  }

  // Value Extraction
  {
    QVariant variant = "42";
    int intValue = variant.toInt(); // Extract the stored value as an int

    QVariant variant2 = QVariant::fromValue(QDate(2021, 7, 1));
    QDate dateValue = variant2.toDate(); // Extract the stored value as a QDate
  }

  // Value Assignment
  {
    QVariant variant;
    variant = 42;               // Assigning an int value
    variant = QString("World"); // Assigning a QString value
  }

  // Comparison and Equality:
  {
    QVariant variant1 = 42;
    QVariant variant2 = 42.0;

    bool isEqual =
        (variant1 == variant2); // Compare two QVariant objects for equality
  }

  // Serialization and Deserialization
  {
    //        QVariant variant = 42;
    //        QByteArray serializedData = variant.save(); // Serialize the
    //        QVariant to a byte array

    //        QVariant deserializedVariant;
    //        deserializedVariant.load(serializedData); // Deserialize the
    //        QVariant from the byte array
  }
}
