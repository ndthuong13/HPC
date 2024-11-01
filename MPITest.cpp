//Tính tổng các phần tử của ma trận bằng MPI
//Yêu cầu :
//•	Đầu vào : Một ma trận kích thước n×n(n = 1000, các phần tử sinh ngẫu nhiên đa luống).
//•	Đầu ra : Tổng các phần tử của ma trận.
//•	Thuật toán :
//o	Ma trận được chia thành các hàng và phân phối cho các tiến trình.
//o	Mỗi tiến trình tính tổng các phần tử của các hàng mà nó nhận được.
//o	Kết quả được gửi về tiến trình gốc, tiến trình gốc sẽ tính tổng toàn bộ ma trận.
//Kỹ thuật : Sử dụng : MPI_Init, MPI_Comm_size, MPI_Comm_rank, MPI_Send, MPI_Recv, và MPI_Finalize
//#include <mpi.h>
//#include <iostream>
//#include <vector>
//#include <cstdlib>
//#include <ctime>
//
//const int N = 1000; // Kích thước ma trận
//
//// Hàm để sinh ma trận ngẫu nhiên
//void generateRandomMatrix(std::vector<std::vector<int>>& matrix) {
//    srand(time(0)); // Khởi tạo seed ngẫu nhiên
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            matrix[i][j] = rand() % 100; // Phần tử ngẫu nhiên trong khoảng từ 0 đến 99
//        }
//    }
//}
//
//int main(int argc, char** argv) {
//    MPI_Init(&argc, &argv);
//
//    int rank, size;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Lấy ID của tiến trình hiện tại
//    MPI_Comm_size(MPI_COMM_WORLD, &size); // Lấy số lượng tiến trình
//
//    int rows_per_process = N / size; // Số hàng mỗi tiến trình sẽ xử lý
//    int start_row = rank * rows_per_process;
//    int end_row = (rank + 1) * rows_per_process;
//
//    // Ma trận và tổng
//    std::vector<std::vector<int>> matrix;
//    int total_sum = 0;
//
//    // Tiến trình gốc (rank 0) sẽ sinh ma trận ngẫu nhiên và phân phối dữ liệu
//    if (rank == 0) {
//        matrix.resize(N, std::vector<int>(N));
//        generateRandomMatrix(matrix);
//    }
//
//    // Tiến trình gốc gửi các hàng của ma trận đến các tiến trình khác
//    std::vector<int> local_matrix(rows_per_process * N);
//    if (rank == 0) {
//        for (int i = 1; i < size; i++) {
//            MPI_Send(matrix[i * rows_per_process].data(), rows_per_process * N, MPI_INT, i, 0, MPI_COMM_WORLD);
//        }
//        // Copy các hàng cho tiến trình gốc
//        for (int i = 0; i < rows_per_process; i++) {
//            for (int j = 0; j < N; j++) {
//                local_matrix[i * N + j] = matrix[i][j];
//            }
//        }
//    }
//    else {
//        MPI_Recv(local_matrix.data(), rows_per_process * N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//    }
//
//    // Mỗi tiến trình tính tổng các phần tử trong hàng mà nó nhận được
//    int local_sum = 0;
//    for (int i = 0; i < rows_per_process; i++) {
//        for (int j = 0; j < N; j++) {
//            local_sum += local_matrix[i * N + j];
//        }
//    }
//
//    // Gửi tổng của mỗi tiến trình về tiến trình gốc
//    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
//
//    // Tiến trình gốc hiển thị tổng toàn bộ ma trận
//    if (rank == 0) {
//        std::cout << "Tong cac phan tu cua ma tran la: " << total_sum << std::endl;
//    }
//
//    MPI_Finalize();
//    return 0;
//}

//Bài 6: Tính trung bình cộng của mảng bằng MPI
//Yêu cầu :
//•	Đầu vào : Một mảng số nguyên(n = 100000000, khởi tạo ngẫu nhiên đa luồng).
//•	Đầu ra : Giá trị trung bình của các phần tử trong mảng.
//•	Thuật toán : Chia mảng cho các tiến trình, mỗi tiến trình tính tổng của phần mình, sau đó sử dụng MPI_Reduce để tính tổng toàn cục và chia cho số phần tử.
//Kỹ thuật : MPI_Init, MPI_Comm_size, MPI_Comm_rank, MPI_Scatter, MPI_Reduce, MPI_Finalize
//#include <mpi.h>
//#include <iostream>
//#include <vector>
//#include <cstdlib>
//#include <ctime>
//
//const int N = 100000000; // Kích thước mảng
//
//// Hàm để sinh mảng ngẫu nhiên
//void generateRandomArray(std::vector<int>& array) {
//    srand(time(0)); // Khởi tạo seed ngẫu nhiên
//    for (int i = 0; i < N; i++) {
//        array[i] = rand() % 100; // Phần tử ngẫu nhiên trong khoảng từ 0 đến 99
//    }
//}
//
//int main(int argc, char** argv) {
//    MPI_Init(&argc, &argv);
//
//    int rank, size;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Lấy ID của tiến trình hiện tại
//    MPI_Comm_size(MPI_COMM_WORLD, &size); // Lấy số lượng tiến trình
//
//    int elements_per_process = N / size; // Số phần tử mỗi tiến trình sẽ xử lý
//    std::vector<int> array;
//    std::vector<int> local_array(elements_per_process);
//
//    // Tiến trình gốc (rank 0) sẽ sinh mảng ngẫu nhiên
//    if (rank == 0) {
//        array.resize(N);
//        generateRandomArray(array);
//    }
//
//    // Chia mảng cho các tiến trình bằng MPI_Scatter
//    MPI_Scatter(array.data(), elements_per_process, MPI_INT, local_array.data(),
//        elements_per_process, MPI_INT, 0, MPI_COMM_WORLD);
//
//    // Mỗi tiến trình tính tổng các phần tử của phần mình
//    long long local_sum = 0;
//    for (int i = 0; i < elements_per_process; i++) {
//        local_sum += local_array[i];
//    }
//
//    // Thu thập tổng cục bộ từ các tiến trình về tiến trình gốc
//    long long global_sum = 0;
//    MPI_Reduce(&local_sum, &global_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
//
//    // Tiến trình gốc tính giá trị trung bình
//    if (rank == 0) {
//        double average = static_cast<double>(global_sum) / N;
//        std::cout << "Gia tri trung binh cua cac phan tu trong mang la: " << average << std::endl;
//    }
//
//    MPI_Finalize();
//    return 0;
//}



//Bài 1: Tính tổng các phần tử trong một mảng bằng MPI
//Yêu cầu :
//•	Đầu vào : Một mảng số nguyên(gồm 100000000 triệu số ngẫu nhiên).
//•	Đầu ra : Tổng các phần tử trong mảng.
//•	Thuật toán : Chia mảng cho các tiến trình.Mỗi tiến trình tính tổng các phần tử trong phần của mình, sau đó sử dụng MPI_Reduce để tính tổng toàn bộ.
//Kỹ thuật : MPI_Init, MPI_Comm_size, MPI_Comm_rank, MPI_Scatter, MPI_Reduce, MPI_Finalize
//#include <mpi.h>
//#include <iostream>
//#include <vector>
//#include <cstdlib>
//#include <ctime>
//
//const int N = 100000000; // Kích thước mảng
//
//// Hàm để sinh mảng ngẫu nhiên
//void generateRandomArray(std::vector<int>& array) {
//    srand(time(0)); // Khởi tạo seed ngẫu nhiên
//    for (int i = 0; i < N; i++) {
//        array[i] = rand() % 100; // Phần tử ngẫu nhiên trong khoảng từ 0 đến 99
//    }
//}
//
//int main(int argc, char** argv) {
//    MPI_Init(&argc, &argv);
//
//    int rank, size;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Lấy ID của tiến trình hiện tại
//    MPI_Comm_size(MPI_COMM_WORLD, &size); // Lấy số lượng tiến trình
//
//    int elements_per_process = N / size; // Số phần tử mỗi tiến trình sẽ xử lý
//    std::vector<int> array;
//    std::vector<int> local_array(elements_per_process);
//
//    // Tiến trình gốc (rank 0) sẽ sinh mảng ngẫu nhiên
//    if (rank == 0) {
//        array.resize(N);
//        generateRandomArray(array);
//    }
//
//    // Chia mảng cho các tiến trình bằng MPI_Scatter
//    MPI_Scatter(array.data(), elements_per_process, MPI_INT, local_array.data(),
//        elements_per_process, MPI_INT, 0, MPI_COMM_WORLD);
//
//    // Mỗi tiến trình tính tổng các phần tử của phần mình
//    long long local_sum = 0;
//    for (int i = 0; i < elements_per_process; i++) {
//        local_sum += local_array[i];
//    }
//
//    // Thu thập tổng cục bộ từ các tiến trình về tiến trình gốc
//    long long global_sum = 0;
//    MPI_Reduce(&local_sum, &global_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
//
//    // Tiến trình gốc in ra tổng toàn bộ
//    if (rank == 0) {
//        std::cout << "Tong cac phan tu trong mang la: " << global_sum << std::endl;
//    }
//
//    MPI_Finalize();
//    return 0;
//}
