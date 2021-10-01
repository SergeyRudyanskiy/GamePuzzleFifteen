#include "gameboard.h"
#include <random>
#include <QDebug>

namespace  {
bool is_adjacent(const GameBoard::Position& position_first, const GameBoard::Position& position_second){
    if(position_first == position_second) { return false; }

    const auto calculate_distance = [](const size_t pos_first, const size_t pos_second) {
        int distance = static_cast<int>(pos_second - pos_first);
        return std::abs(distance);
    };

    bool result = false;
    if(position_first.first == position_second.first) {
        int distance = calculate_distance(position_first.second, position_second.second);
        if(distance == 1) { result = true; }
    }
    else if(position_first.second == position_second.second) {
        int distance = calculate_distance(position_first.first, position_second.first);
        if(distance == 1) { result = true; }
    }

    return result;
}
}

GameBoard::GameBoard(const size_t board_dimension, QObject *parent) : QAbstractListModel(parent), m_board_dimension(board_dimension), m_board_size(m_board_dimension * m_board_dimension), m_hidden_element_value(m_board_size) {
    Q_ASSERT(m_board_dimension > 0);

    m_vec_board.resize(m_board_size);
    std::iota(m_vec_board.begin(), m_vec_board.end(), 1);
    shuffle();
}

bool GameBoard::is_board_complete() const {
    for(size_t current_element = 0; current_element < m_vec_board.size(); ++current_element) {
        if(m_vec_board[current_element].value != current_element + 1) { return false; }
    }

    return true;
}

bool GameBoard::is_adjacent_simple(const GameBoard::ElementIt& element_first, const GameBoard::ElementIt& element_second) const {
    size_t distance = static_cast<size_t>(std::abs(std::distance(element_first, element_second)));
    return distance == m_board_dimension || distance == 1;
}

GameBoard::Position GameBoard::get_position_on_board(size_t element_index) const {
    size_t posiztion_x = element_index % m_board_dimension;
    size_t posiztion_y = element_index / m_board_dimension;

    return std::make_pair(posiztion_x, posiztion_y);
}

bool GameBoard::is_valid_position(const size_t position) const { return position < m_board_size; }
size_t GameBoard::board_dimension() const { return m_board_dimension; }
size_t GameBoard::hidden_element_value() const { return m_hidden_element_value; }
int GameBoard::rowCount(const QModelIndex& parent) const { Q_UNUSED(parent) return m_vec_board.size(); }

QVariant GameBoard::data(const QModelIndex &index, int role) const {
    if(!index.isValid() || role != Qt::DisplayRole) { return QVariant(); }

    const int row_index = index.row();
    if(!is_valid_position(row_index)) { return QVariant(); }

    return QVariant::fromValue(m_vec_board.at(row_index).value);
}

bool GameBoard::move_tile(int index_tile) {
    if (!is_valid_position(static_cast<size_t>(index_tile))) { return false; }

    //Position position_tile = get_position_on_board(static_cast<size_t>(index_tile));

    std::vector<Tile>::iterator it_hidden_element = std::find(m_vec_board.begin(), m_vec_board.end(), m_hidden_element_value);
    std::vector<Tile>::iterator it_tile_element   = std::next(m_vec_board.begin(), index_tile);
    Q_ASSERT(it_hidden_element != m_vec_board.end() && it_tile_element != m_vec_board.end());

    if(!is_adjacent_simple(it_hidden_element, it_tile_element)) { return false; }

    //model change need signal
    std::swap(it_hidden_element->value, m_vec_board[index_tile].value);
    emit dataChanged(createIndex(0, 0), createIndex(static_cast<int>(m_board_size), 0));

    if(is_board_complete()) { qDebug() << "complete"; }
    return true;
}

void GameBoard::shuffle() {
    static int64_t seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937_64 generator(seed);

    do {
        std::shuffle(m_vec_board.begin(), m_vec_board.end(), generator);
    } while (!is_valid_board_simple());

    emit dataChanged(createIndex(0, 0), createIndex(static_cast<int>(m_board_size), 0));
}

bool GameBoard::is_valid_board_merge() const { return 0; }
bool GameBoard::is_valid_board_simple() const {
    size_t inversion_count = 0;

    for (size_t idx_elem_first = 0; idx_elem_first < m_board_size - 1; ++idx_elem_first) {
        for (size_t idx_elem_second = idx_elem_first + 1; idx_elem_second < m_board_size; ++idx_elem_second) {
            if(m_vec_board[idx_elem_first].value  != m_hidden_element_value
            && m_vec_board[idx_elem_second].value != m_hidden_element_value
            && m_vec_board[idx_elem_first].value > m_vec_board[idx_elem_second].value) {
                ++inversion_count;
            }
        }
    }

    if (m_board_dimension & 1) { return !(inversion_count & 1); }
    else {
        size_t distance = std::abs(std::distance(m_vec_board.begin(), std::find(m_vec_board.begin(), m_vec_board.end(), m_hidden_element_value)));
        qDebug() << m_board_dimension - (get_position_on_board(distance).second);
        return ((m_board_dimension - get_position_on_board(distance).second) & 1) ? !(inversion_count & 1) : inversion_count & 1;
    }
}
