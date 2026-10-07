#pragma once

#include <QLayout>
#include <QRect>

namespace Base
{

class FlowLayout : public QLayout
{
public:
	explicit FlowLayout(QWidget* parent = nullptr);
	virtual ~FlowLayout() = default;

	void addItem(QLayoutItem* item) override;
	void insertWidget(int index, QWidget* widget);
	void changeWidget(int index, QWidget* widget);
	void moveWidget(int from, int to);

	QLayoutItem* itemAt(int index) const override;
	QLayoutItem* takeAt(int index) override;
	int count() const override;

	Qt::Orientations expandingDirections() const override;
	bool hasHeightForWidth() const override;
	int heightForWidth(int width) const override;

	QSize sizeHint() const override;
	QSize minimumSize() const override;
	void setGeometry(const QRect& rect) override;

private:
	int doLayout(const QRect& rect, bool test_only) const;

private:
	QList<QLayoutItem*> _items;
};

} // namespace Base
