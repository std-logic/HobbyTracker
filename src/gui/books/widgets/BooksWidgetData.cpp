#include "BooksWidgetData.h"

#include <gui/base/widgets/BaseComboEdit.h>
#include <gui/base/widgets/BaseWidgetRating.h>

#include <QLineEdit>

Books::WidgetData::WidgetData(size_t index, const DataList& data_list, QWidget* parent)
	: Base::WidgetData{index, data_list.size(), parent}
	, _data_list{data_list}
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
	if (_mode_edit_data) { _data = _data_list[_index]; }
}

void Books::WidgetData::initCommonParams()
{
	setWindowTitle(_mode_edit_data ?
			tr("Редактирование данных произведения") :
			tr("Добавление нового произведения"));
	setMinimumWidth(550);
}

void Books::WidgetData::initWidgets()
{
	add(tr("Автор:"), _combo_author_tr);

	add(tr("Автор (ориг.):"), _combo_author_orig);
	_combo_author_orig->lineEdit()->setPlaceholderText(tr("Необязательное поле"));

	add(tr("Название:"), _edit_title_tr);

	add(tr("Название (ориг.):"), _edit_title_orig);
	_edit_title_orig->setPlaceholderText(tr("Необязательное поле"));

	add(tr("Жанр:"), _combo_genre);

	add(tr("Год:"), _edit_year);
	_edit_year->setValidator(new QIntValidator(1, 2100, _edit_year));

	add(tr("Оценка:"), _widget_rating);
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
	if (_combo_author_tr->currentText().isEmpty()) {
		emit showMessage(tr("Не введён автор!"));
		return false;
	}
	_data.setAuthorTr(_combo_author_tr->currentText());

	_data.setAuthorOrig(_combo_author_orig->currentText());

	if (_edit_title_tr->text().isEmpty()) {
		emit showMessage(tr("Не введено название!"));
		return false;
	}
	_data.setTitleTr(_edit_title_tr->text());

	_data.setTitleOrig(_edit_title_orig->text());

	if (_combo_genre->currentText().isEmpty()) {
		emit showMessage(tr("Не введён жанр!"));
		return false;
	}
	_data.setGenre(_combo_genre->currentText());

	if (!_edit_year->hasAcceptableInput()) {
		emit showMessage(tr("Не введён год!"));
		return false;
	}
	_data.setYear(_edit_year->text().toUInt());

	if (!_widget_rating->isValid()) {
		emit showMessage(tr("Не выбрана оценка!"));
		return false;
	}
	_data.setRating(_widget_rating->rating());

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
