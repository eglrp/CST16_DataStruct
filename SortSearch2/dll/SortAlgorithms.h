#ifndef __SORT_ALGORITHMS_H__
#define __SORT_ALGORITHMS_H__

/**
* 算法名称	 ：直接插入排序
* 算法描述	 ：依次从无序区中选择记录插入到有序区中的合适位置使之依然有序。
* 时间复杂度 ：O(n^2)
* 空间复杂度 ：O(1)
* 稳定排序	 ：是
*/
void insert_sort(int* array, int length);


/**
* 算法名称	 ：希尔排序（插入排序的一种）
* 算法描述	 ：先将整个待排记录序列分割成若干个子序列（由相隔某个“增量”
*			   的记录组成的）分别进行直接插入排序，然后逐渐缩减增量
*			   （最终缩小至 1）再对各组分别进行直接插入排序。
* 时间复杂度 ：O(n^2)，记录较多时比直接插入排序快。
* 空间复杂度 ：O(1)
* 稳定排序	 ：否
*/
void shell_sort(int* array, int length);


/**
* 算法名称	 ：冒泡排序（交换排序的一种）
* 算法描述	 ：将 length 个记录看作按纵向排列，每趟排序时自下至上对每对相邻
*             记录进行比较，若次序不符合要求（逆序）就交换。每趟排序结束时
*             都能使排序范围内关键字最小的记录象一个气泡一样升到表上端的
*             对应位置，整个排序过程共进行 length - 1 趟，依次将关键字最小、
*			   次小 … 的各个记录“冒到”表的第一个、第二个 … 位置上。
* 时间复杂度 ：O(n^2)
* 空间复杂度 ：O(0)
* 稳定排序	 ：是
*/
void bubble_sort(int* array, int length);


/**
* 算法名称	 ：冒泡排序改进版（交换排序的一种）
* 算法描述   ：在每趟冒泡扫描中，记住最后一次交换发生的位置 lastExchange，
*			   （该位置之前的相邻记录均已有序）。下一趟排序开始时，
*             [0, lastExchange] 是有序区，[lastExchange + 1, length - 1] 是
*             无序区。这样，一趟排序可能使当前有序区扩充多个记录，从而减少排序的趟数。
* 时间复杂度 ：O(n^2)
* 空间复杂度 ：O(0)
* 稳定排序	 ：是
*/
void bubble_sort_opt(int* array, int length);


/**
* 算法名称	 ：快速排序（交换排序的一种）
* 算法描述	 ：快速排序是一种分治法，在 [low, high] 中任选一个记录作为基准记录(Pivot)，
*             以此基准将当前无序区划分为左、右两个较小的子区间 [low, pivotpos - 1)
*             和 [pivotpos + 1, high]，并使左边子区间中所有记录均小于等于基准记录，
*             右边的子区间中所有记录均大于等于基准记录。
*             通过递归调用快速排序对左、右子区间进行划分，直至每个子区间只有一个记录。
* 时间复杂度 ：平均：O(nlgn)，最坏：O(n^2)
* 空间复杂度 ：O(lgn)
* 稳定排序	 ：否
*/
void quick_sort(int* array, int length);


/**
* 算法名称	  ：直接选择排序（选择排序的一种）
* 算法描述	  ：第 i 趟排序开始时，当前有序区和无序区分别为 [0, i - 1] 和
*              [i, length - 1]。该趟排序从当前无序区中选出关键字最小的记录 [k]，
*              将它与无序区的第一个记录 [i] 交换，使 [0, i] 和 [i + 1, length - 1]
*              分别变为记录个数增加一个的新有序区和记录个数减少一个的新无序区。
* 时间复杂度  ：O(n^2)
* 空间复杂度  ：O(0)
* 稳定排序	  ：否
*/
void selection_sort(int* array, int length);


/**
* 算法名称	 ：堆排序（树形选择排序的一种）
* 算法描述	 ：在排序过程中，将 [0, length - 1] 看成是一棵完全二叉树的
*             顺序存储结构，利用完全二叉树中双亲结点和孩子结点之间的内
*             在关系（双亲结点总是孩子结点大或小），在当前无序区中选择
*             最大（或最小）的记录。
* 时间复杂度 ：O(nlgn)
* 空间复杂度 ：O(1)
* 稳定排序	 ：否
*/
void heap_sort(int* array, int length);


/**
* 算法名称	 ：归并排序
* 算法描述	 ：将待排序记录数组分解为两个记录数组 [0, m]，[m + 1, length - 1]，
*             并将之合并到一个临时数组 temp ，待合并完成后将 temp 复制回数组中。
* 时间复杂度 ：O(lgn)
* 空间复杂度 ：O(n)
* 稳定排序	 ：是
*/

// 用分治法自下向上进行二路归并排序
//
void merge_sort(int* array, int length);

// 用分治法自上向下进行二路归并排序
//
void merge_sort_dc(int* array, int length);

/**
* 算法名称	 ：计数排序
* 算法描述	 ：
* 时间复杂度 ：O(n)
* 空间复杂度 ：O(n + m)
* 稳定排序	 ：是
* 使用限制	 ：待排序记录均为小于等于 k 的正整数。
*/
void counting_sort(int* array, int length, int k);


/**
* 算法名称	 ：箱/桶排序
* 算法描述	 ：将长度为 N 待排序序列划分成 M 个的子区间（桶）；然后基于
*              某种映射函数，将待排序列的关键字 k 映射到第 i 个桶中（即桶数组
*              B 的下标 i ），那么该关键字 k 就作为 B[i] 中的元素（每个桶 B[i]
*              都是一组大小为N/M的序列）；接着对每个桶 B[i] 中的所有元素进行
*              比较排序（可以使用快速排序）；然后依次枚举输出 B[0]....B[M] 中的
*              全部内容即是一个有序序列。
* 时间复杂度 ：O(n)
* 空间复杂度 ：O(n + m)
* 稳定排序	 ：是
*/

// 在这里只对正数排序
//
void bucket_sort(int* array, int length);


/**
* 算法名称	 ：基数排序
* 算法描述	 ：基数排序是对桶排序的改进和推广，从低位到高位依次对关键字的
*              各个分量Kj(j = d - 1，d - 2，…，0)进行桶排序。
* 时间复杂度 ：O(n)
* 空间复杂度 ：O(n + m)
* 稳定排序	 ：是
*
*/

// 在这里只对正数排序
//
void radix_sort(int* array, int length);

#endif // __SORT_ALGORITHMS_H__