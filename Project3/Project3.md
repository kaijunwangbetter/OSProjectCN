<!-- vscode-markdown-toc -->
* 1. [1 Introduction](#Introduction)
* 2. [2 Implementation Details](#ImplementationDetails)
	* 2.1. [2-1 The code framework](#Thecodeframework)
	* 2.2. [2-2 Init the array](#Initthearray)
	* 2.3. [2-3 Init the threads and sort the arrays](#Initthethreadsandsortthearrays)
	* 2.4. [2-4 Merge and sort the arrays](#Mergeandsortthearrays)
	* 2.5. [2-5 The main fuction](#Themainfuction)
* 3. [3 Program Results](#ProgramResults)
* 4. [1 Introduction](#Introduction-1)
* 5. [2 Implementation Details](#ImplementationDetails-1)
	* 5.1. [2-1 The code framework](#Thecodeframework-1)
	* 5.2. [2-2 Finish the 2 sorting function](#Finishthe2sortingfunction)
	* 5.3. [2-3 Achieve the small part conquer](#Achievethesmallpartconquer)
	* 5.4. [2-4 Add the threads](#Addthethreads)
	* 5.5. [2-5 The main function](#Themainfunction)
* 6. [3 Program Results](#ProgramResults-1)

<!-- vscode-markdown-toc-config
	numbering=true
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc --># Project3: ***Multithreaded Sorting Application*** & ***Fork-Join Sorting Application***

王凯俊          520021910282



# Project3-1: Multithreaded Sorting Application
##  1. <a name='Introduction'></a>1 Introduction
In this program, we will conduct a program which can using multithreaded methods to sort the arrays and merge them into one array.
The program is structured as the figure below:
![image-20220416](C:\Users\86184\Desktop\Project3\1.png)

##  2. <a name='ImplementationDetails'></a>2 Implementation Details
###  2.1. <a name='Thecodeframework'></a>2-1 The code framework
To finish this project, there are 333 parts to be finished:
1. init the array
2. init the threads and sort the arrays
3. merge and sort the arrays
   

###  2.2. <a name='Initthearray'></a>2-2 Init the array
We should first set the array and waiting the input.
The detailed code is as below:

```c
#define MAX_NUM 100
int array[MAX_NUM];
size_t array_size = 0;
// set the array 
printf("Please enter the number of elements:");
    scanf("%ld", &array_size);
    for(size_t i = 0; i != array_size; ++i) {
        scanf("%d", &array[i]);
// input data and store in the array  

```

###  2.3. <a name='Initthethreadsandsortthearrays'></a>2-3 Init the threads and sort the arrays
To sort two arrays, we should set 2 threads.
The init code is as below:

```c:
pthread_t tid[2];
pthread_attr_t attr;
```
Then we want to achieve our sorting goals, we use the "runner" as the function to sort the arrays.

The runners function is as below:
```c

void *runner(void *param) {
    size_t low, high;
    low = ((parameters *)param)->low;
    high = ((parameters *)param)->high;
    qsort(array + low, high - low, sizeof(int), cmp);
    // cmp means the compare function
    pthread_exit(0);
}
int cmp(const void  *a, const void *b) {
    return *((int *)a) - *((int *)b);
}
```

We want to call the *runner* function in the main fuction with 2 threads, the detailed code is as below:
```c
    pthread_attr_init(&attr);
    /* create two threads to sort the two halves of the array */
    for(size_t i = 0; i != 2; ++i) {
        pthread_create(&tid[i], &attr, runner, &data[i]);
    }
    /* now wait for the thread to exit */
    for(size_t i = 0; i != 2; ++i) {
        pthread_join(tid[i], NULL);
    }
```

###  2.4. <a name='Mergeandsortthearrays'></a>2-4 Merge and sort the arrays
After sort two arrays respectively, we want to merge and sort these two arrays into one array.
The detailed code is as below:
```c
void merge_array(int *result) {
    size_t low1 = 0, high1 = array_size / 2;
    size_t low2 = array_size / 2, high2 = array_size;
    size_t i = 0;
    while(low1 < high1 && low2 < high2) {
        if(array[low1] < array[low2]) {
            result[i++] = array[low1++];
        } else {
            result[i++] = array[low2++];
        }
    }
    if(low2 < high2) {
        low1 = low2, high1 = high2;
    }
    while(low1 < high1) {
        result[i++] = array[low1++];
    }
}
```

###  2.5. <a name='Themainfuction'></a>2-5 The main fuction
After the steps above, the basic framework has been made.And we want to connect these modes using the main function.
The code in main function is as below:
```c
int main() {
    pthread_t tid[2];
    pthread_attr_t attr; //set the threads
    init_array();
    printf("Original array:\n");
    print_array(array, array_size);
    parameters data[2];
    data[0].low = 0;
    data[0].high = array_size / 2;
    data[1].low = array_size / 2;
    data[1].high = array_size;
    pthread_attr_init(&attr);
    // create two threads to sort the two halves of the array 
    for(size_t i = 0; i != 2; ++i) {
        pthread_create(&tid[i], &attr, runner, &data[i]);
    }
    // wait for the thread to exit */
    for(size_t i = 0; i != 2; ++i) {
        pthread_join(tid[i], NULL);
    }
    printf("Thread 0:\n");
    print_array(array, array_size / 2);
    printf("Thread 1:\n");
    print_array(array + array_size / 2, array_size - array_size / 2);
    int *sorted_array = malloc(sizeof(int) * array_size);
    merge_array(sorted_array);
    printf("After merging:\n");
    print_array(sorted_array, array_size);
    return 0;
}
```

##  3. <a name='ProgramResults'></a>3 Program Results
Complie the program:

```c
gcc multithread_sorting.c -o multithread_sorting -l pthread
```
Then type **./multithread_sorting** to execute it.

And the result is as below:

Input 10 elements:

![image-20220416](C:\Users\86184\Desktop\Project3\2.png)

Input 20 elements:

![image-20220416](C:\Users\86184\Desktop\Project3\3.png)

# Project3-2: Fork-Join Sorting Application
##  4. <a name='Introduction-1'></a>1 Introduction
Implement the preceding project (Multithreaded Sorting Application) using Java’s fork-join parallelism API. This project will be developed in two different versions. Each version will implement a different divide-and-conquer sorting algorithm:
1. Quicksort
2. Mergesort
   
We want to divide the data and for both the Quicksort and Mergesort algorithms,
when the list to be sorted falls within some threshold value (for example, the
list is size 100 or fewer), directly apply a simple algorithm such as the Selection
or Insertion sort.

There has been an example about sum function, we need to modify it to achieve our sorting goals.

##  5. <a name='ImplementationDetails-1'></a>2 Implementation Details
###  5.1. <a name='Thecodeframework-1'></a>2-1 The code framework
We first see the **sum** function. then we realise that we need to conduct the two sorting functions in the large part.And then we should use the selection sort or something to achieve the small part conquer.And apparently, we need use the Java api to achieve the thread pool.

So there are total 3 steps to achieve:

1. finish the 2 sorting function
2. achieve the small part conquer
3. add the threads

###  5.2. <a name='Finishthe2sortingfunction'></a>2-2 Finish the 2 sorting function
We should achieve the quicksort and mergesort using the Java grammer.

Luckily, there are not much difference between C and Java. So we can achieve it using a C-likely way.
The detaeled code is as below:

The quicksort:
```Java
    int i=low;
    int j=high;
    int pivot = array[low];
    if(low>=high)
        return;
    while(low<high)
    {
        while(low<high && pivot<=array[high])
            high--;
        if(pivot > array[high])
        {
            int tmp;
            tmp = array[low];
            array[low] = array[high];
            array[high] =tmp;
            ++low;
        }
        while (low < high && pivot >= array[low])
        {
        ++low; 
        }
        if (pivot < array[low])
        {
            int tmp;
            tmp = array[low];
            array[low] = array[high];
            array[high] =tmp;
            --high;
        }
    }
    quick_sort_pivot(i, low-1); 
    quick_sort_pivot(low+1, j);
```

The merge sort:
```Java
        int current1=left;
        int current2=mid+1;
        int copy_id =left;
        int[] array_copy = new int[SIZE];
        while(current1<=mid && current2<=right)
        {
            if(array[current1]<=array[current2])
                {
                    array_copy[copy_id]=array[current1];
                    current1++;
                    copy_id++;
                }
            else
            {
                array_copy[copy_id]=array[current2];
                current2++;
                copy_id++;
            }
        }
        if(copy_id==right)
        {
            for(int i=left;i<=right;i++)
                array[i]=array_copy[i];
        }
        else if(current1<mid)
        {
            for(int i=current1;i<=mid;i++)
                {
                    array_copy[copy_id]=array[i];
                    copy_id++;
                }
            for(int i=left; i<=right;i++)
                array[i]=array_copy[i];
        }
        else if(current2<right)
        {
                for(int i=current2;i<=right;i++)
                {
                    array_copy[copy_id]=array[i];
                    copy_id++;
                }
                for(int i=left; i<=right;i++)
                    array[i]=array_copy[i];
        }   
            
    }
```

###  5.3. <a name='Achievethesmallpartconquer'></a>2-3 Achieve the small part conquer
We want to achieve the conquer part using the selection sort.

The detailed code is as below:
```Java
private void selection_sort(int low, int high)
    {
        for(int i=low;i<high;i++)
        {
            int min = array[i];
            for(int j=i+1;j<=high;j++)
                {
                    if(array[j]<min)
                    {
                        min = array[j];
                        array[j] = array[i];
                        array[i] = min;
                    }
                }
        }
    }
```


###  5.4. <a name='Addthethreads'></a>2-4 Add the threads
We use fork-join parallelism to get the array.

```Java
		SortTask task = new SortTask(0, SIZE-1, array);
		pool.invoke(task);
```

###  5.5. <a name='Themainfunction'></a>2-5 The main function
We want to input some random numbers to test our program.
So we use the **rand.nextInt()** to achieve it.

Then we want to do our function and output the results on the screen.

The detailed code is as below:

```Java
	public static void main(String[] args) 
    {
		ForkJoinPool pool = new ForkJoinPool();
		int[] array = new int[SIZE];

		// create SIZE random integers between 0 and 100
		java.util.Random rand = new java.util.Random(100);

		System.out.println("Init array is: ");

		for (int i = 0; i < SIZE; i++) {
			array[i] = rand.nextInt(10);
            
            System.out.print(array[i]);
            System.out.print(' ');
		}		
		
		SortTask task = new SortTask(0, SIZE-1, array);

		pool.invoke(task);
        System.out.println(' ');

		System.out.println("Sorted array is: ");
        for (int i = 0; i < SIZE; i++) {
            System.out.print(array[i]);
            System.out.print(' ');
		}
	}
```

##  6. <a name='ProgramResults-1'></a>3 Program Results
The result is as below:

The **quick_sort** with random **from 0 to 100**:

![image-20220416](C:\Users\86184\Desktop\Project3\4.png)

![image-20220416](C:\Users\86184\Desktop\Project3\5.png)

The **merge_sort** with random **from 0 to 20**:

![image-20220416](C:\Users\86184\Desktop\Project3\6.png)

![image-20220416](C:\Users\86184\Desktop\Project3\7.png)


# Conclusion and Thoughts
In project 3-1, we learned about using C language to implement a multithread program, based on the **pthread** library.
In project 3-2, we utilize **fork-join** in Java, similar to the multithread in C. 

I learned about the Java grammer and api.

I also know some about the threads' knowledge.

I review the completion of quick sort and merge sort.

All in all, it's a good experience which enhance my coding ability.

