/**

@author Mattia Basaglia

@section License

    Copyright (C) 2015 Mattia Basaglia

    This software is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This software is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Color Widgets.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef COLOR_WIDGETS_COLOR_PALETTE_WIDGET_HPP
#define COLOR_WIDGETS_COLOR_PALETTE_WIDGET_HPP

#include <memory>
#include <QWidget>
#include "color_palette_model.hpp"
#include "swatch.hpp"

namespace color_widgets {

/**
 * \brief A widget to use and modify palettes
 */
class ColorPaletteWidget : public QWidget
{
    Q_OBJECT

    /**
     * \brief Model used to store the palettes
     */
    Q_PROPERTY(ColorPaletteModel* model READ model WRITE setModel NOTIFY modelChanged)

    /**
     * \brief Size of a single color in the swatch widget
     */
    Q_PROPERTY(QSize colorSize READ colorSize WRITE setColorSize NOTIFY colorSizeChanged)
    /**
     * \brief Policy for colorSize
     **/
    Q_PROPERTY(color_widgets::Swatch::ColorSizePolicy colorSizePolicy READ colorSizePolicy WRITE setColorSizePolicy NOTIFY colorSizePolicyChanged)

    /**
     * \brief Forces the Swatch to display that many rows of colors
     *
     * If there are too few elements, the widget will display less than this
     * many rows.
     *
     * A value of0 means that the number of rows is automatic.
     *
     * \note Conflicts with forcedColumns
     */
    Q_PROPERTY(int forcedRows READ forcedRows WRITE setForcedRows NOTIFY forcedRowsChanged)

    /**
     * \brief Forces the Swatch to display that many columns of colors
     *
     * If there are too few elements, the widget will display less than this
     * many columns.
     *
     * A value of 0 means that the number of columns is automatic.
     *
     * \note Conflicts with forcedRows
     */
    Q_PROPERTY(int forcedColumns READ forcedColumns WRITE setForcedColumns NOTIFY forcedColumnsChanged)

    /**
     * \brief Whether the palettes can be modified via user interaction
     */
    Q_PROPERTY(bool readOnly READ readOnly WRITE setReadOnly NOTIFY readOnlyChanged)

    /**
     * \brief Currently selected color
     */
    Q_PROPERTY(QColor currentColor READ currentColor WRITE setCurrentColor NOTIFY currentColorChanged)

public:
    ColorPaletteWidget(QWidget* parent = nullptr);
    ~ColorPaletteWidget();

    ColorPaletteModel* model() const;

    /**
     * \brief Currently selected palette
     * \pre model() != nullptr and there is a selected palette
     */
    const ColorPalette& currentPalette() const;

    QSize colorSize() const;
    Swatch::ColorSizePolicy colorSizePolicy() const;

    int forcedRows() const;
    int forcedColumns() const;

    bool readOnly() const;
    QColor currentColor() const;

public slots:
    void setModel(ColorPaletteModel* model);
    void setColorSize(const QSize& colorSize);
    void setColorSizePolicy(Swatch::ColorSizePolicy colorSizePolicy);
    void setForcedRows(int forcedRows);
    void setForcedColumns(int forcedColumns);
    void setReadOnly(bool readOnly);
    /**
     * \brief Attempt to select a color
     *
     * If the given color is available in the current palete, it will be selected
     * \return \b true on success
     */
    bool setCurrentColor(const QColor& color);
    /**
     * \brief Attempt to select a color by name
     *
     * If the given color is available in the current palete, it will be selected
     * \return \b true on success
     */
    bool setCurrentColor(const QString& name);

signals:
    void modelChanged(ColorPaletteModel* model);
    void colorSizeChanged(const QSize& colorSize);
    void colorSizePolicyChanged(Swatch::ColorSizePolicy colorSizePolicy);
    void forcedRowsChanged(int forcedRows);
    void forcedColumnsChanged(int forcedColumns);
    void readOnlyChanged(bool readOnly);
    void currentColorChanged(const QColor& currentColor);

private slots:
    void on_palette_list_currentIndexChanged(int index);
    void on_swatch_doubleClicked(int index);

private:
    class Private;
    std::unique_ptr<Private> p;
};

} // namespace color_widgets
#endif // COLOR_WIDGETS_COLOR_PALETTE_WIDGET_HPP
