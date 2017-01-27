#include "QAbstractItemViewResult.h"
#include <QModelIndex>
#include <QAbstractItemModel>

QModelIndex findIndexByString(const QAbstractItemModel* model, const QString& text,  const QModelIndex& parent = QModelIndex());
QModelIndex findIndexByString(const QModelIndex& index, const QString& text) {
    // First check this particular index
    if(index.data().toString() == text)
        return index;
    // Check if it has children and loop
    const QAbstractItemModel* model = index.model();
    if(model==nullptr)
        return QModelIndex();
    if (!model->hasChildren(index))
        return QModelIndex();
    return findIndexByString(model, text, index);
}
QModelIndex findIndexByString(const QAbstractItemModel* model, const QString& text,  const QModelIndex& parent) {
    int rows = model->rowCount(parent);
    int cols = model->columnCount(parent);
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j) {
        QModelIndex index_child = findIndexByString(model->index(i, j, parent), text);
        if(index_child.isValid())
            return index_child;
      }
    return QModelIndex();
}
QModelIndex findIndexByString(const QAbstractItemView* view, const QString& text) {
    //const QModelIndex root = view->rootIndex();
    const QAbstractItemModel* model = view->model();
    return findIndexByString(model, text);
}

QAbstractItemViewResult::QAbstractItemViewResult(QAbstractItemView*i, TestingModule*m)
 : WidgetResult(i, m)
 , targetView_(i)
{

}
void QAbstractItemViewResult::doubleClickItem(const QString& name)
{
    QModelIndex index(findIndexByString(targetView_, name));
    //QString indexData = index.data().toString();
    if(index.isValid()) {
        targetView_->doubleClicked(index);
    }
}
void QAbstractItemViewResult::selectItems(const QStringList& list)
{
    if(list.size() > 0) {
        // first item clears the selection and is added
        // all following items are added
        QItemSelectionModel::SelectionFlags flags = QItemSelectionModel::ClearAndSelect;
        const QAbstractItemView::SelectionBehavior behavior = targetView_->selectionBehavior();
        QItemSelection selection;
        Q_FOREACH(const QString& text, list) {
            const QModelIndex index(findIndexByString(targetView_, text));
            //QItemSelection selection;
            //selection.
            //QString indexData = index.data().toString();
            if(index.isValid()) {
                // If whole rows are to be selected, expand the item to view width
                if(behavior == QAbstractItemView::SelectRows) {
                    QModelIndex begin, end, tmp;
                    begin = end = index;
                    // find first sibling in the same row that is valid
                    while((tmp=begin.sibling(begin.row(), begin.column()-1)).isValid()) {
                        begin = tmp;
                    }
                    // and now move all the way to last item
                    while((tmp=end.sibling(end.row(), end.column()+1)).isValid()) {
                        end = tmp;
                    }
                    selection.select(begin, end);
                }
                // Same as above but with columns
                else if(behavior == QAbstractItemView::SelectColumns) {
                    QModelIndex begin, end, tmp;
                    begin = end = index;
                    while((tmp=begin.sibling(begin.row()-1, begin.column())).isValid()) {
                        begin = tmp;
                    }
                    while((tmp=end.sibling(end.row()+1, end.column())).isValid()) {
                        end = tmp;
                    }
                    selection.select(begin, end);
                }
                else {
                    selection.select(index, index);
                }
            }
            // No longer clear following items
            //flags = flags&(~QItemSelectionModel::Clear);
        }
        targetView_->selectionModel()->select(selection, flags);
    }
}
