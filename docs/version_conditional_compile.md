```cpp
#include <QtGlobal>

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)

  QObject::connect(reply, &QNetworkReply::errorOccurred,
                   std::bind(&printFromattedErrorOccurred, reply));
#endif
```
