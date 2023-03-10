/*******************************************************************************
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 ******************************************************************************/

#ifndef QPL_TEST_COMPRESSION_FIXTURE_HPP
#define QPL_TEST_COMPRESSION_FIXTURE_HPP

#include <vector>

#include "qpl/cpp_api/operations/compression_operation.hpp"

#include "gtest/gtest.h"
#include "gtest/gtest-param-test.h"

#include "qpl_test_environment.hpp"
#include "source_provider.hpp"
#include "test_cases.hpp"
#include "high_level_api_util.hpp"
#include "random_generator.h"

namespace qpl::test {

struct CompressionTestCase {
    std::string      file_name = "";
    mini_block_sizes mini_block_size = mini_block_size_none;
    bool             gzip_mode       = false;
    uint32_t         chunk_size      = 0;
};

static std::ostream &operator<<(std::ostream &os, const CompressionTestCase &test_case) {
    os << "file name: " << test_case.file_name << "\n";
    os << "Gzip mode: " << (test_case.gzip_mode ? "Enabled" : "Disabled") << "\n";
    os << "Mini-block size: " << mini_block_size_to_string(test_case.mini_block_size) << "\n";
    os << "Chunk size: " << test_case.chunk_size << "\n";
    return os;
}

class CompressionFixture : public testing::Test,
                           public TestCases<CompressionTestCase> {
protected:
    void SetUp() override;

    void SetUpBeforeIteration() override;

    [[nodiscard]] auto GetSeed() const -> uint32_t;

    [[nodiscard]] auto GetExecutionPath() const -> qpl_path_t;

    virtual void SetBuffers();

    std::vector<uint8_t> source;
    std::vector<uint8_t> destination;
    std::vector<uint8_t> reference_destination;
    CompressionTestCase  current_test_case;
    random               chunk_size_generator;

private:
    uint32_t   m_seed;
    qpl_path_t m_execution_path;
};

enum class zero_vector_generation_type {
    zero_vector,
    random_vector,
    generated_vector
};

struct ZeroCompressionTestCase {
    uint32_t                    number_of_input_elements = 0;
    zero_input_format           input_format             = zero_input_format::word_16_bit;
    zero_vector_generation_type vector_generation_type   = zero_vector_generation_type::zero_vector;
};

static std::ostream &operator<<(std::ostream &os, const ZeroCompressionTestCase &test_case) {
    os << "Input format: "
       << (test_case.input_format == zero_input_format::word_16_bit ? "16" : "32")
       << " bits word"
       << "\n";
    os << "Number of input elements: " << test_case.number_of_input_elements << "\n";
    std::string vector_generation_type;

    if (test_case.vector_generation_type == zero_vector_generation_type::zero_vector) {
        vector_generation_type = "Zero vector";
    } else if (test_case.vector_generation_type == zero_vector_generation_type::random_vector) {
        vector_generation_type = "Random vector";
    } else if (test_case.vector_generation_type == zero_vector_generation_type::generated_vector) {
        vector_generation_type = "Generated vector";
    } else {
        vector_generation_type = "Unknown";
    }

    os << "Vector generation type: " << vector_generation_type << "\n";

    return os;
}

class ZeroCompressionFixture : public JobFixture,
                               public TestCases<ZeroCompressionTestCase> {
protected:
    void SetUp() override;

    void SetUpBeforeIteration() override;

    virtual void SetBuffers();

    virtual void InitializeTestCases() = 0;

    void CleanUpAfterIteration() override;

    std::vector<uint8_t>    compressed_data;
    std::vector<uint8_t>    reference_compressed_data;
    std::vector<uint8_t>    reference_destination;
    ZeroCompressionTestCase current_test_case;
};

}

#endif // QPL_TEST_COMPRESSION_FIXTURE_HPP
