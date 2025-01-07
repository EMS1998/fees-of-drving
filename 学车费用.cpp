#include <stdio.h>
#include <string.h>
#include<stdlib.h>

typedef struct {
	int id;
	char name[11];
	int total;
	int rank;  // 用来存储排名
} student;

int compare(const void *a, const void *b) {
	const student *s1 = (const student *)a;
	const student *s2 = (const student *)b;
	
	// 按学车费用排序（总费用从大到小）
	if (s1->total != s2->total) {
		return s2->total - s1->total;  // s2排前面
	}
	
	// 如果总费用相同，按姓名排序（ASCII码升序）
	int name_cmp = strcmp(s1->name, s2->name);
	if (name_cmp != 0) {
		return name_cmp;
	}
	
	// 如果总费用和姓名都相同，按id升序排序
	return s1->id - s2->id;
}

int main() {
	int n;
	printf("请输入学生人数: ");
	scanf("%d", &n);
	
	// 确保学生人数不超过20
	if (n > 20) {
		printf("人数不能超过20\n");
		return 1;
	}
	
	student students[20];
	
	// 输入学生信息
	for (int i = 0; i < n; i++) {
		students[i].id = i + 1;
		students[i].total = 0;
		students[i].rank = 1;  // 初始化rank为1
		
		printf("请输入学生%d的姓名和费用（费用用空格分隔）：", i + 1);
		// 输入姓名
		scanf("%s", students[i].name);
		
		// 输入费用，直到遇到换行符结束
		int fee;

		while (scanf("%d", &fee) == 1) {
			students[i].total += fee;
			if (getchar() == '\n') break;  // 一行输入结束
		}
	}
	
	// 使用qsort排序
	qsort(students, n, sizeof(student), compare);
	
	// 计算排名
	int current_rank = 1;
	for (int i = 0; i < n; i++) {
		// 对于每个学生，填充rank值
		if (i > 0 && students[i].total != students[i - 1].total) {
			current_rank = i + 1;  // 费用不同，重新计算排名
		}
		students[i].rank = current_rank;
	}
	
	// 输出排序后的结果
	printf("\n排序后的结果：\n");
	for (int i = 0; i < n; i++) {
		printf("费用排名: %d, 编号: %d, 名字: %s, 总费用: %d\n", students[i].rank, students[i].id, students[i].name, students[i].total);
	}
	
	return 0;
}

