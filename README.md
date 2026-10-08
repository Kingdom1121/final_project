# BÁO CÁO TIẾN ĐỘ TUẦN 1 — ĐỒ ÁN CUỐI KỲ

> **Học phần:** Cấu trúc dữ liệu và Giải thuật (Data Structures and Algorithms)  
> **Mã lớp học phần:** `DASA230179_Dot1` — HK1 2026-2027  
> **Giảng viên hướng dẫn (GVHD):** ThS. Huỳnh Xuân Phụng  
> **Đề tài:** Backtracking Search for the N-Queens Problem  
> **Kho lưu trữ (Repository):** [Kingdom1121/DSA_Cuoi_Ky_Final_Project](https://github.com/Kingdom1121/DSA_Cuoi_Ky_Final_Project)  
> **Trạng thái:** Đã cập nhật và chỉnh sửa theo góp ý của GVHD

## 1. Giới thiệu đề tài

Bài toán **N-Queens** là bài toán kinh điển trong lý thuyết tìm kiếm tổ hợp (Combinatorial Search) được Donald Knuth chọn làm ví dụ nền tảng trong tài liệu **TAOCP (Vol. 4A/4B)** để phân tích kỹ thuật cắt tỉa (Pruning). 

Dự án tập trung xây dựng, đánh giá thực nghiệm và phân tích hiệu năng giữa hai phương pháp:
1. **Plain Backtracking:** Duyệt đặt quân hậu theo từng hàng, kiểm tra xung đột cột và đường chéo bằng bảng tra cứu mảng đánh dấu `vector<bool>` trong thời gian O(1).
2. **Bitmask Backtracking (Knuth's Algorithm):** Biểu diễn trạng thái cột và các đường chéo bằng các số nguyên (bitmask), sử dụng các phép toán bitwise cấp độ thanh ghi CPU (`available & -available`, dịch bit `<< 1`, `>> 1`) để cắt tỉa tối đa các nhánh thừa.

---
## 2. Các nội dung đã chỉnh sửa & tối ưu trong mã nguồn

Dựa trên mã nguồn ban đầu và yêu cầu làm rõ điều kiện đặt quân hậu, các thay đổi cụ thể gồm:

* **Tách riêng hàm kiểm tra điều kiện cho Plain Backtracking (`isSatisfyPlain`):**
  * Gom toàn bộ logic kiểm tra cột và hai đường chéo (`d1`, `d2`) ra hàm riêng thay vì viết gộp trong vòng lặp.
  * Giúp mã nguồn thể hiện rõ điều kiện an toàn $O(1)$ trước khi đặt quân hậu: `!cols[col] && !diag1[d1] && !diag2[d2]`.

* **Tách riêng hàm kiểm tra cho Bitmask Backtracking (`isSatisfyBitmask`):**
  * Tách biểu thức logic `((colmask | ld | rd) & bit) == 0` thành hàm riêng để làm rõ điều kiện bất biến (vị trí bit không giao với bất kỳ tia chiếu nào).

* **Đồng bộ hóa quy ước đếm node (`nodes++`):**
  * Đặt biến đếm `nodes++` ngay tại đầu mỗi hàm đệ quy của cả hai phương pháp để đảm bảo đo đạc công bằng trên cùng một không gian trạng thái.

* **Bổ sung chú thích giải trình thuật toán:**
  * Ghi chú rõ ý nghĩa hình học của đường chéo chính ($d_1 = row - col + n - 1$), đường chéo phụ ($d_2 = row + col$) và mặt nạ bit `all_ones = (1 << n) - 1`.

