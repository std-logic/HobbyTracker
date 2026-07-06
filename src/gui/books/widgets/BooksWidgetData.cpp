#include "BooksWidgetData.h"

#include <gui/base/widgets/BaseComboEdit.h>
#include <gui/base/widgets/BaseWidgetRating.h>

#include <QLineEdit>

Books::WidgetData::WidgetData(size_t index, const DataList& list, QWidget* parent)
	: Base::WidgetData{parent}
	, _index{index}
	, _data_list{list}
{
	initData();
	initCommonParams();
	initWidgets();
	copyDataToGui();

	// strictly after initialization finished, because we need only real changes
	connect(_combo_author_tr, &Base::ComboEdit::currentIndexChanged,
			this, &WidgetData::authorTrChanged);
}

void Books::WidgetData::initData()
{
	if (_index < _data_list.size()) { _data = _data_list[_index]; }
}

void Books::WidgetData::initCommonParams()
{
	setWindowTitle((_index < _data_list.size()) ?
					tr("Редактирование данных произведения") :
					tr("Добавление нового произведения"));
}

void Books::WidgetData::initWidgets()
{
	addWidget(tr("Автор:"), _combo_author_tr = new Base::ComboEdit(this));

	addWidget(tr("Автор (ориг.):"), _combo_author_orig = new Base::ComboEdit(this));
	_combo_author_orig->lineEdit()->setPlaceholderText(tr("Необязательное поле"));

	addWidget(tr("Название:"), _edit_title_tr = new QLineEdit(this));

	addWidget(tr("Название (ориг.):"), _edit_title_orig = new QLineEdit(this));
	_edit_title_orig->setPlaceholderText(tr("Необязательное поле"));

	addWidget(tr("Жанр:"), _combo_genre = new Base::ComboEdit(this));

	addWidget(tr("Год:"), _edit_year = new QLineEdit(this));
	_edit_year->setValidator(new QIntValidator(1, 2100, _edit_year));

	addWidget(tr("Оценка:"), _widget_rating = new Base::WidgetRating(this));
}

void Books::WidgetData::copyDataToGui()
{
	_combo_author_tr->setTextAndList(_data.authorTr(), _data_list.listOfAuthorsTr());

	_combo_author_orig->setTextAndList(_data.authorOrig(), _data_list.listOfAuthorsOrig());

	_edit_title_tr->setText(_data.titleTr());

	_edit_title_orig->setText(_data.titleOrig());

	_combo_genre->setTextAndList(_data.genre(), _data_list.listOfGenres());

	_edit_year->setText(_data.yearString());

	_widget_rating->setRating(_data.rating());
}

bool Books::WidgetData::copyGuiToData()
{
	_data.setAuthorTr(_combo_author_tr->currentText());
	if (_data.authorTr().isEmpty()) {
		emit showMessage(tr("Не введён автор!"));
		return false;
	}

	_data.setAuthorOrig(_combo_author_orig->currentText());

	_data.setTitleTr(_edit_title_tr->text());
	if (_data.titleTr().isEmpty()) {
		emit showMessage(tr("Не введено название!"));
		return false;
	}

	_data.setTitleOrig(_edit_title_orig->text());

	_data.setGenre(_combo_genre->currentText());
	if (_data.genre().isEmpty()) {
		emit showMessage(tr("Не введён жанр!"));
		return false;
	}

	_data.setYear(_edit_year->text().toUInt());
	if ((_data.year() < 1) || (2100 < _data.year())) {
		emit showMessage(tr("Не введён год!"));
		return false;
	}

	_data.setRating(_widget_rating->rating());
	if ((_data.rating() < 1) || (10 < _data.rating())) {
		emit showMessage(tr("Не выбрана оценка!"));
		return false;
	}

	return true;
}

void Books::WidgetData::save()
{
	if (copyGuiToData()) {
		emit saveData(_index, _data);
		close();
	}
}

void Books::WidgetData::authorTrChanged(int index)
{
	if (index >= 0) {
		auto author_orig = _data_list.findAuthorOrigByTr(_combo_author_tr->itemText(index));
		_combo_author_orig->lineEdit()->setText(author_orig);
	}
}
