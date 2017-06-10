# JOI Spring Camp 2015 Day 1

Test có tại [http://www.ioi-jp.org/camp/2015/2015-sp-tasks/2015-sp-d1-data.zip](http://www.ioi-jp.org/camp/2015/2015-sp-tasks/2015-sp-d1-data.zip).

## copypaste2
### Vị trí từng kí tự
Xét kí tự ở vị trí `i` trong xâu ban đầu. Sau khi thực hiện truy vấn `a b c`, vị trí mới của `i` sẽ là:

- `i` nếu `i < c`.
- `i + b - a` nếu `i >= c`.

Ngoài ra, nếu `a <= i < b`, ta có một phiên bản mới của `i` nằm ở `c + i - a`. Đồng thời `i` cũng có thể bị xóa nếu nằm ngoài `M`.

Với những điều kiện trên, hiển nhiên ta có thể tính được vị trí mới của `i` sau khi thực hiện `N` truy 
vấn trong `O(N)`. Tuy nhiên ta sẽ không tìm được kết quả mong muốn nếu suy nghĩ theo hướng này. 

Cần phải nghĩ ngược lại, kí tự `i` ở xâu cuối cùng đứng đâu ở xâu đầu tiên?

### Lật ngược suy nghĩ!
Xét kí tự ở vị trí `i` trong xâu cuối cùng. **Trước khi** thực hiện truy vấn `a b c` cuối cùng, vị trí của kí tự đó là:
- `i` nếu `i < c`.
- `i - (b - a)` nếu `i >= c + (b - a)`.
- `a + i - c` nếu `c <= i < c + (b - a)`.

Không có điều kiện gì khác, ta có thể dễ dàng tìm được vị trí ban đầu của một kí tự trong xâu cuối bằng cách lần ngược từng truy vấn. Độ phức tạp là `O(N)` cho mỗi kí tự.

Như vậy tổng độ phức tạp là `O(KN)`.

## enjoi
### Quy hoạch động
Không khó để nhìn ra hàm quy hoạch động hiển nhiên sau:
 - Gọi `f[i][j]` là chi phí biến đoạn `[i .. i + (4 ^ j))` thành xâu bậc `j`. Hiển nhiên `f[i][0] = 0` với mọi `i`.
 - `f[i][j]` sẽ được tính từ `f[i + 3 * (4 ^ (j - 1))][j - 1]`, cộng chi phí biến 3 đoạn `4 ^ (j - 1)` thành kí tự `J`, `O`, `I` tương ứng.

Nếu giải quyết được đoạn tính phần biến đổi `J,O,I` trong `O(1)`, ta sẽ có hàm qhđ độ phức tạp `O(4^K * K)`, thỏa mãn bài toán.

### Tính nhanh
Số kí tự phải thay đổi trong đoạn `i..j` để thành `k` sẽ là `length(i..j) - count(i..j, k)`. Vì chỉ có
3 kí tự nên ta có thể tính trước mảng dồn `count` trong `O(N)`. 

## growing2
### Cắt đôi
Để thuận tiện ta gọi cây mà trong đáp án thỏa mãn `j < i` là thỏa mãn trái, ngược lại là thỏa mãn phải.

Nếu cây `i` được chọn thỏa mãn trái, tức tất cả các cây `j < i` và `H[j] > H[i]` đều phải bị chặt bỏ.

Xét `i < j` và `i` thỏa mãn phải, `j` thỏa mãn trái.
Hiển nhiên `H[i] = H[j]`, và `i` thỏa mãn trái đồng thời `j` thỏa mãn phải.

Từ đó, ta có thể nhận thấy luôn tồn tại một vị trí `i` mà mọi cây `< i` ra quả trong đáp án đều thỏa mãn trái, `>= i` ra quả trong đáp án đều thỏa mãn phải. Ta sẽ xét riêng 2 đoạn và cộng vào nhau.

### Quy hoạch động
Gọi  `f[i]` là chi phí để tạo ra một loạt cây thỏa mãn trái, trong đó cây phải cùng là `i`. Ta sẽ thêm dần từng cây từ 1 đến `N` rồi cập nhật dần các `f[i]`. Giả sử ta đã có đến cây thứ `x`, ta sẽ coi như `f[i] = inf` với mọi `i > x`. 

Bắt đầu thêm cây `x + 1`. Việc đầu tiên là tính `f[x + 1]`. Việc này rất đơn giản: Ta chỉ cần lấy một trong các `f[i]` đứng trước mà `H[i] <= H[x + 1]`  rồi thêm cây `x + 1` vào chuỗi. Nói cách khác, `f[x + 1] = max(f[i]) + P[x + 1]` với mọi `i <= x` và `H[i] <= H[x + 1]`.

Việc tiếp theo là xử lí các `f[i]` đứng trước đó. Nếu `H[i] >= H[x + 1]`, ta có thể bỏ qua `x + 1`, không phải chặt cây `x + 1` nhưng nó cũng không ra quả. Nếu `H[i] < H[x + 1]`, để duy trì `f[i]` đúng định nghĩa (`i` là cây phải cùng thỏa mãn trái), ta bắt buộc phải chặt `x + 1`.
Nói cách khác, `f[i] -= C[x + 1]` với mọi `i <= x` và `H[i] < H[x + 1]`.

Để có thể ghép, ta tính `pre[x] = max(f[i])` với `i <= x` sau khi thêm cây `x`. Hiển nhiên ta coi như các cây `> x` không tồn tại, vì chúng không ảnh hưởng đến tập thỏa mãn trái.

Với cách tính tương tự, ta có mảng `suf[x]` để tính thỏa mãn phải, và đáp án là `max(pre[x - 1], suf[x])` với `1 <= x <= N + 1`. 

Thuật toán này có độ phức tạp `O(N^2)`, ta sẽ tiếp tục cải tiến xuống `O(N log N)`.

### Giá trị đại diện?
Xét lại thuật toán trên, có phải rằng `f[i]` với `i` là chỉ số không hề quan trọng? 

Khi đã thêm cây `x`, xét `i < j <= x` mà `H[i] = H[j]`. Dễ dàng nhận thấy `f[j] > f[i]`. Như vậy, với mỗi chiều cao ta chỉ cần lấy cây xa nhất có độ cao đó.

Nhận ra điều này, ta không lưu `f[i]` với `i` là chỉ số cây cuối cùng nữa - đổi thành `i` là **độ cao** cây cuối cùng. 

Ơ hay, một lần đọc nữa và ta nhận ra mọi điều kiện `H[i]...` ở trên giờ đều trỏ đến 1 prefix của `f[]`! Như vậy, mọi vòng for bây giờ đều trở thành một thao tác có thể dùng IT để cập nhật/truy vấn trong `O(log N)`. 

Độ phức tạp trở thành `O(N log N)`.

## ioioi_cards
Để đơn giản, ta coi dãy bit là `A[]` có độ dài `M = A + B + C + D + E` (đánh số từ 0).
### Biến đổi!
Xét dãy `B[]` có độ dài `M + 1` như sau: 

- `B[0] = 0`.
- `B[i] = A[i - 1] ^ A[i]` với `0 < i < M`. 
- `B[M] = 0`.

Ta có thể nhận thấy một số tính chất sau:

 - Truy vấn flip `L..R` trở thành flip `B[L]` và `B[R + 1]`.
 - Dãy `A[]` thành toàn 1 khi và chỉ khi `B[]` toàn 0.
 - Ban đầu, dãy `B[]` chỉ gồm 4 số 1 ở các vị trí `A`, `A + B`, `A + B + C`, `A + B + C + D`.

Để biến dãy `B[]` thành toàn 0, ta được dùng các truy vấn flip 2 bit nào đó với giá cho trước.

### Đường đi
Dễ dàng nhận thấy khi flip 2 bit trái nhau, số lượng bit 1 không đổi. Như vậy, để tắt 2 bit `i` và `j` ta cần tìm một dãy truy vấn có dạng `(i, k1), (k1, k2), ..., (k[x - 1], k[x]), (k[x], j)` với tổng cost bé nhất. 

Nếu coi mỗi bit `B[i]` là một đỉnh, một truy vấn flip là một cạnh...

Chính xác, tắt 2 bit `i` - `j` chính là tìm đường đi ngắn nhất giữa 2 đỉnh này.

### Giải quyết bài toán!
Chỉ có 4 bit 1, vậy bài toán chỉ là với mọi cách chia thành 2 cặp, tìm đường đi ngắn nhất giữa 2 cặp này.

Thật may mắn, chỉ có 3 cách chia cặp, vậy độ phức tạp chỉ là `O(3 * (M + N) log N)`.