# IOIOI Cards

- Thời gian: 1s
- Bộ nhớ: 256MB

Ngài *K* rất thích bói toán, và rất hay tổ chức các cuộc bói toán đủ thể loại. Hôm nay, ông quyết định sẽ tiên đoán kết quả của đội IOI Nhật Bản năm nay bằng một cỗ bài với chữ `I` đính mặt trước và `O` đính mặt sau!

Cách bói toán của ông có thể được diễn tả như sau:

- Đầu tiên, chọn ra 5 số nguyên $A, B, C, D, E$.
- Đặt $A + B + C + D + E$ quân bài lên bài theo thứ tự sau từ trái sang phải: $A$ con bài ngửa, $B$ con bài sấp, $C$ ngửa, $D$ sấp, $E$ ngửa. Các con bài sẽ xếp thành dãy `I O I O I` với số lượng kí tự từng loại tương ứng.
- Chọn một số trong $N$ thao tác được định trước và làm chúng theo một thứ tự nào đó. Một loại thao tác có thể thực hiện nhiều lần. Mỗi thao tác có dạng: lật tất cả quân bài từ vị trí $L_i$ đến $R_i$. Mất 1 giây để lật 1 quân bài, vậy thao tác thứ $i$ mất $R_i - L_i + 1$ giây để thực hiện.
- Sau khi thực hiện, nếu tất cả quân bài đều ngửa, thì kết quả nhận được là thành công!

Để tránh phải ngồi lật bài cả ngày, ông *K* muốn biết trước liệu việc bói toán có thể trả về thành công không? Nếu có, thời gian lật bài nhanh nhất để 
đưa về thành công là bao nhiêu?

## Yêu cầu
Cho thứ tự ban đầu của các quân bài và $N$ loại thao tác định trước, xác định tính khả thi và số bước lật ít nhất để kết quả nhận được là thành công.

## Dữ liệu nhập vào
Hãy đọc từ standard input dữ liệu theo định dạng sau:

- Dòng đầu tiên gồm 5 số $A$, $B$, $C$, $D$ và $E$. 5 số này xác định thứ tự ban đầu của các quân bài. 
- Dòng tiếp theo ghi số $N$, số loại thao tác định trước.
- $N$ dòng tiếp theo, dòng thứ $i$ gồm 2 số $L_i$ và $R_i$, miêu tả thao tác loại $i$. Khi thực hiện thao tác loại $i$ ta lật tất cả quân bài từ $L_i$ đến $R_i$, tốn $R_i - L_i + 1$ giây.

## Dữ liệu in ra
Hãy in ra standard output một dòng duy nhất ghi:

- `-1` nếu không có cách làm thỏa mãn.
- Thời gian thực hiện ngắn nhất, nếu có cách.

## Giới hạn
Trong tất cả các test:

- $1 \le A, B, C, D, E \le 100 000$.
- $1 \le N \le 100 000$.
- $1 \le L_i \le R_i \le A + B + C + D + E$ với mọi $1 \le i \le N$.

## Subtask
### Subtask 1 (15 điểm)

- $N \le 15$ với mọi test.

### Subtask 2 (50 điểm)

- $A, B, C, D, E \le 50$ với mọi test.

### Subtask 3 (35 điểm)
Không có điều kiện gì thêm.

## Ví dụ
### Input 1
```
1 2 3 4 5
3
2 3
2 6
4 10
```
### Output 1
```
12
```

Trạng thái ban đầu của các quân bài là `IOOIIIOOOOIIIII`. 

Thực hiện thao tác số 2, trạng thái trở thành `IIIOOOOOOOIIIII`. Thao tác này mất 5 giây.

Thực hiện thao tác 3, trạng thái trở thành `IIIIIIIIIIII`, kết quả bói là thành công! Thời gian thực hiện là 7 giây.

Ta có thể thành công trong 12 giây. Đây cũng là đáp án tối ưu.

### Input 2
```
1 1 1 1 1
1
1 1
```
### Output 2
```
-1
```

Hiển nhiên ta không thể thực hiện thành công. Ta in `-1`.