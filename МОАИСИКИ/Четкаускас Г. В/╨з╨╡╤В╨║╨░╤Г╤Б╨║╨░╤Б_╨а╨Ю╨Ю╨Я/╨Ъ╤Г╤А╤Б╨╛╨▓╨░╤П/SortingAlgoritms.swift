struct SortingAlgorithms {
    static func radixSort(_ array: inout [String]) {
        let radix = 10  // Основа для чисел (10 цифр)
        var done = false
        var digit = 0  // Начиная с младшего разряда
        
        while !done {
            done = true
            var buckets: [[String]] = Array(repeating: [], count: radix)
            
            for number in array {
                if digit < number.count {
                    let index = number.index(number.endIndex, offsetBy: -digit - 1)
                    let characterValue = Int(String(number[index])) ?? 0
                    buckets[characterValue].append(number)
                    done = false
                } else {
                    buckets[0].append(number)
                }
            }
            
            var i = 0
            for bucket in buckets {
                for number in bucket {
                    array[i] = number
                    i += 1
                }
            }
            
            digit += 1
        }
    }

    // Быстрая сортировка с разделением Хоара для числовых массивов с учетом подсчета сравнений и пересылок
        static func quickSortHoare(_ array: inout [Int], comparisons: inout Int, swaps: inout Int) {
            quickSortHoare(&array, low: 0, high: array.count - 1, comparisons: &comparisons, swaps: &swaps)
        }
        
        private static func quickSortHoare(_ array: inout [Int], low: Int, high: Int, comparisons: inout Int, swaps: inout Int) {
            if low < high {
                let p = partitionHoare(&array, low: low, high: high, comparisons: &comparisons, swaps: &swaps)
                quickSortHoare(&array, low: low, high: p, comparisons: &comparisons, swaps: &swaps)
                quickSortHoare(&array, low: p + 1, high: high, comparisons: &comparisons, swaps: &swaps)
            }
        }
        
        private static func partitionHoare(_ array: inout [Int], low: Int, high: Int, comparisons: inout Int, swaps: inout Int) -> Int {
            let pivot = array[low]
            var i = low - 1
            var j = high + 1
            
            while true {
                repeat {
                    j -= 1
                    comparisons += 1
                } while array[j] > pivot

                repeat {
                    i += 1
                    comparisons += 1
                } while array[i] < pivot
                
                if i < j {
                    array.swapAt(i, j)
                    swaps += 1
                } else {
                    return j
                }
            }
        }
}
