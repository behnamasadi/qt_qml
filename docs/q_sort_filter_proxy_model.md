# QSortFilterProxyModel
Qt provides `QSortFilterProxyModel` that simplifies adding both sorting and filtering capabilities features.

In our example, I'll start with `QSortFilterProxyModel` as a base class instead of `QAbstractProxyModel` for simplicity. This means we get the sorting and filtering functionality by default and only need to override the desired behavior.

Let's add these functionalities:

1. **Sorting**: We will sort the strings based on their original form.
2. **Filtering**: Let's filter out any strings that don't contain the letter 'a'.

```cpp
class SortFilterStringProxyModel : public QSortFilterProxyModel {
  Q_OBJECT

public:
  SortFilterStringProxyModel(QObject *parent = nullptr)
      : QSortFilterProxyModel(parent) {}

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override {
    if (!index.isValid() || role != Qt::DisplayRole)
      return QVariant();

    QVariant originalData =
        QSortFilterProxyModel::sourceModel()->data(mapToSource(index), role);

    return originalData;
  }

protected:
  bool filterAcceptsRow(int sourceRow,
                        const QModelIndex &sourceParent) const override {
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    return sourceModel()->data(index).toString().contains("a");
  }
};

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  QStringListModel sourceModel;
  sourceModel.setStringList(QStringList() << "apple"
                                          << "berry"
                                          << "cherry"
                                          << "date"
                                          << "fig");

  SortFilterStringProxyModel proxyModel;
  proxyModel.setSourceModel(&sourceModel);

  // Apply sorting
  proxyModel.sort(0);

  // Now let's print out the  data from the proxy model
  for (int i = 0; i < proxyModel.rowCount(); i++) {
    QModelIndex proxyIndex = proxyModel.index(i, 0);
    qDebug() << proxyModel.data(proxyIndex).toString();
  }

  return app.exec();
}
```

Key Changes:
1. Inherited from `QSortFilterProxyModel` for sorting and filtering capabilities.
2. Overridden `filterAcceptsRow` to implement the filtering based on the letter 'a'.
3. Used `proxyModel.sort(0);` to sort the strings in ascending order by default.

When you run the code, it should output:

```
"apple"
"date"
```

Here, only the strings containing the letter 'a' are shown, and they are sorted based on their original form (i.e., "apple", "cherry", "date"), but displayed in their reversed form.

## filterAcceptsRow

The `filterAcceptsRow` method is one of the central mechanisms of the `QSortFilterProxyModel` class. When you use a proxy model that inherits from `QSortFilterProxyModel`, this function is utilized to determine whether a particular row from the source model should be displayed in the view that's using the proxy model.

Here's a general outline of how it works:

1. **Source Model Update**: Whenever there's a change in the source model (like adding/removing items), `QSortFilterProxyModel` gets notified because it listens to the various signals emitted by the source model. These signals include things like `rowsInserted`, `rowsRemoved`, `dataChanged`, etc.

2. **Invalidate Filter**: If the filter needs to be reapplied, either due to source model changes or if you explicitly call methods like `invalidateFilter()`, the proxy model will internally go through each row of the source model.

3. **`filterAcceptsRow` Call**: For each row of the source model, the proxy model calls `filterAcceptsRow`. This function should return `true` if the row should be visible through the proxy (i.e., the row "passes" the filter criteria) and `false` otherwise.

4. **Resulting Model**: The `QSortFilterProxyModel` then constructs its internal mapping based on the results from these calls. Only rows for which `filterAcceptsRow` returned `true` are "visible" in the proxy model and thus accessible to views using the proxy model.

So, to sum up, whenever something triggers a reevaluation of the filtered state of the model, `filterAcceptsRow` gets called for each row in the source model to determine if it should be included in the proxy model.

In the context of the example I provided earlier, whenever there's a change to the `sourceModel` data, `filterAcceptsRow` will be called for each item in the `sourceModel`. If an item contains the letter "a", the function returns `true` and that item will be "visible" in the proxy model. Otherwise, the item will be excluded from the proxy model.


## sort

In the given example, the `QSortFilterProxyModel::sort()` function was called, which internally uses the `lessThan` method to determine the order of items in the proxy model. However, we didn't override the `lessThan` method in the example, so it uses the default behavior provided by `QSortFilterProxyModel`.

Let's break down how the sorting works based on the example:

1. **Calling `sort()`**:
    In the example, we called:
    ```cpp
    proxyModel.sort(0);
    ```
    This means we're sorting based on column 0 (typically the only column in a list model). By default, this will sort in ascending order.

2. **Default `lessThan` Behavior**:
    The default behavior of `lessThan` in `QSortFilterProxyModel` compares data from the source model based on the specified column. This comparison uses the natural order for the data type, so for strings, it's an alphabetical order.

    Since we didn't override `lessThan`, the source strings ("apple", "berry", "cherry", "date", "fig") are sorted as:
    - apple
    - cherry
    - date
    - berry (this is filtered out because it doesn't contain the letter 'a')
    - fig (this is filtered out because it doesn't contain the letter 'a')

3. **Displaying Sorted Data**:
    After sorting, when you access the data via the proxy model, it still goes through the `data()` method we've overridden. So while the proxy model arranges the rows based on the sorted order of the original strings, it displays the reversed versions of them.

4. **Output**:
    The output then becomes:
    ```
	"apple"
	"date"
    ```

If you wanted to customize the sorting behavior, you could override the `lessThan` method. For instance, if you wanted to sort based on the reversed strings rather than the original strings, you'd implement the `lessThan` method to make that comparison. But in the provided example, we simply relied on the default sorting behavior which sorts the original strings in alphabetical order.
