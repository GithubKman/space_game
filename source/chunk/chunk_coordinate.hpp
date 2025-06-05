#ifndef CHUNK_COORDINATE_HPP
#define CHUNK_COORDINATE_HPP

#include <iostream>

#include "globals.hpp"
#include "vector/vector2i.hpp"
#include "vector/vector2l.hpp"

namespace sms {

class ChunkCoordinate {
private:
    Vector2l m_local;      // Always in [0, 511)
    Vector2i m_chunk;    // Tracks chunk position

    void normalize() {
        // Handle X
	int counter {0};
        while (m_local.GetX() >= g_chunkSize) {
            m_local.ChangeX(-g_chunkSize);
            m_chunk.ChangeX(1);
        }
        while (m_local.GetX() < 0) {
            m_local.ChangeX(g_chunkSize);
            m_chunk.ChangeX(-1);
        }

        // Handle Y
        while (m_local.GetY() >= g_chunkSize) {
            m_local.ChangeY(-g_chunkSize);
            m_chunk.ChangeY(1);
        }
        while (m_local.GetY() < 0) {
            m_local.ChangeY(g_chunkSize);
            m_chunk.ChangeY(-1);
        }
    }

public:
    ChunkCoordinate() : m_local{0, 0}, m_chunk{0, 0} {}

    ChunkCoordinate(Vector2l local, Vector2i chunk)
        : m_local {local}, m_chunk {chunk} {
        normalize();  // Ensure consistency
    }

    void addLocal(Vector2l pos) {
	m_local += pos;
	normalize();
    }

    void addLocal(raylib::Vector2 pos) {
	m_local += pos;
	normalize();
    }

    // Setters
    void setLocal(Vector2l pos) {
        m_local = pos;
        normalize();
    }

    void setLocalX(double x) {
        m_local.SetX(x);
        normalize();
    }

    void setLocalY(double y) {
        m_local.SetY(y);
        normalize();
    }

    void setChunk(Vector2i chunk) {
        m_chunk = chunk;
    }

    void setChunkX(int x) {
        m_chunk.SetX(x);
    }

    void setChunkY(int y) {
        m_chunk.SetY(y);
    }

    // Getters
    Vector2l getLocal() const { return m_local; }
    double getLocalX() const { return m_local.GetX(); }
    double getLocalY() const { return m_local.GetY(); }

    Vector2i getChunk() const { return m_chunk; }
    int getChunkX() const { return m_chunk.GetX(); }
    int getChunkY() const { return m_chunk.GetY(); }

    void print() {
	std::cout << "Local: [" 
		  << m_local.GetX() 
		  << ", " 
		  << m_local.GetY() 
		  << "] Chunk: [" 
		  << m_chunk.GetX() 
		  << ", " 
		  << m_chunk.GetY() 
		  << "]\n";
    }
};

} // namespace sms

#endif
