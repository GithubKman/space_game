#ifndef ID_HPP
#define ID_HPP

class Id {
private:
    int m_id;
public:
    Id(int id) : m_id {id} {}
    Id(const Id& id) : m_id {id.m_id} {}

    int get() {
	return ++m_id;
    }
    int get(int id) {
	return id <= m_id ? ++m_id : m_id = id;
    }
};

#endif
