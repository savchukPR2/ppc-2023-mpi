// Copyright 2023 Savchuk Anton
#include <gtest/gtest.h>
#include "./sleeping_barber.h"

TEST(TESTS, Test_correct ) {
    int rank = 0;
    int sizeWorld = 0;
    MPI_Comm comm = MPI_COMM_WORLD;

    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &sizeWorld);

    int client = sizeWorld - 2;
    int seats = 3;

    if (client < 1) {
        SUCCEED();
    } else {
        if (rank == 0) {
            ASSERT_NO_THROW(CustomRoom(rank, client, seats, comm));
        } else if (rank == 1) {
            ASSERT_NO_THROW(CustomBarber(rank, client, seats, comm));
        } else {
            ASSERT_NO_THROW(CustomClient(rank, client, seats, comm));
        }
    }
}

TEST(TESTS, Test_zero_client) {
    int rank = 0;
    int sizeWorld = 0;
    MPI_Comm comm = MPI_COMM_WORLD;

    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &sizeWorld);

    int client = 0;
    int seats = 3;

    if (rank == 0) {
        ASSERT_ANY_THROW(CustomRoom(rank, client, seats, comm));
    } else if (rank == 1) {
        ASSERT_ANY_THROW(CustomBarber(rank, client, seats, comm));
    } else {
        ASSERT_ANY_THROW(CustomClient(rank, client, seats, comm));
    }
}
TEST(TESTS, Test_zero_seats) {
    int rank = 0;
    int sizeWorld = 0;
    MPI_Comm comm = MPI_COMM_WORLD;

    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &sizeWorld);

    int client = sizeWorld - 2;
    int seats = 0;

    if (rank == 0) {
        ASSERT_ANY_THROW(CustomRoom(rank, client, seats, comm));
    } else if (rank == 1) {
        ASSERT_ANY_THROW(CustomBarber(rank, client, seats, comm));
    } else {
        ASSERT_ANY_THROW(CustomClient(rank, client, seats, comm));
    }
}
TEST(TESTS, Test_zero_client_and_seats) {
    int rank = 0;
    int sizeWorld = 0;
    MPI_Comm comm = MPI_COMM_WORLD;

    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &sizeWorld);

    int client = 0;
    int seats = 0;

    if (rank == 0) {
        ASSERT_ANY_THROW(CustomRoom(rank, client, seats, comm));
    } else if (rank == 1) {
        ASSERT_ANY_THROW(CustomBarber(rank, client, seats, comm));
    } else {
        ASSERT_ANY_THROW(CustomClient(rank, client, seats, comm));
    }
}
TEST(TESTS, Test_one_seat) {
    int rank = 0;
    int sizeWorld = 0;
    MPI_Comm comm = MPI_COMM_WORLD;

    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &sizeWorld);

    int client = sizeWorld - 2;
    int seats = 1;

    if (client < 1) {
        SUCCEED();
    } else {
        if (rank == 0) {
            ASSERT_NO_THROW(CustomRoom(rank, client, seats, comm));
        } else if (rank == 1) {
            ASSERT_NO_THROW(CustomBarber(rank, client, seats, comm));
        } else {
            ASSERT_NO_THROW(CustomClient(rank, client, seats, comm));
        }
    }
}

int main(int argc, char** argv) {
    int result_code = 0;
    int rank = 0;

    ::testing::InitGoogleTest(&argc, argv);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank != 0) {
        delete listeners.Release(listeners.default_result_printer());
    }

    result_code = RUN_ALL_TESTS();
    MPI_Finalize();

    return result_code;
}
