#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QAbstractListModel>
#include <vector> // QVector

namespace  {
struct Tile {
    size_t value;
    Tile& operator= (const size_t new_value) {
        value = new_value;
        return *this;
    }
    bool operator== (size_t other) const { return other == value; }
    bool operator== (const Tile &other) const { return other.value == value; }
};
}

class GameBoard : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int board_dimension READ board_dimension CONSTANT)
    Q_PROPERTY(int hidden_element_value READ hidden_element_value CONSTANT)

public:
    using Position  = std::pair<size_t, size_t>;
    using ElementIt = std::vector<Tile>::iterator;
    static constexpr size_t default_puzzle_dimension = 4;

    GameBoard(const size_t board_dimension = default_puzzle_dimension, QObject* parent = nullptr);

    //need to be implemented as abstract class QAbstractListModel
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    size_t board_dimension() const;
    size_t hidden_element_value() const;

    Q_INVOKABLE bool move_tile(int index_tile);
    Q_INVOKABLE void shuffle();

private:
    std::vector<Tile> m_vec_board;

    const size_t m_board_dimension;
    const size_t m_board_size;
    const size_t m_hidden_element_value;

    bool is_valid_board_merge() const;
    bool is_valid_board_simple() const;

    bool is_valid_position(const size_t position) const;
    bool is_board_complete() const;
    bool is_adjacent_simple(const GameBoard::ElementIt& element_first, const GameBoard::ElementIt& element_second) const;

    Position get_position_on_board(size_t element_index) const;
};

#endif // GAMEBOARD_H
