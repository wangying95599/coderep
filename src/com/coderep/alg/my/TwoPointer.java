package leetcode;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class TwoPointer {
	public static void main(String[] args) {
		String str="abcdabcde121";
		int val = lengthOfLongestSubstring2(str);
		System.out.println(val);
		
		int[] a = {1, 8, 6, 2, 5, 4, 8, 3, 7};
		int max = maxArea(a);
		System.out.println("max          "+max);
		
		int[] s= {-1, 0, 1, 2, -1, -4};
		List list = threeSum(s);
		System.out.println(list);
		
		int[] data= {1,2,3,4,5,6,7,8,9};
		ListNode head=null;
		for(int i:data) {
			ListNode n = new ListNode(i);
			
		}
		removeDuplicates(new int[]{1,2,2,2,3,4,4,5});
		
		findSubstring("barfoothefoobarman",new String[] {"foo", "bar"});
	}
	
	public static int lengthOfLongestSubstring(String s) {
        int n = s.length();
        Set<Character> set = new HashSet<Character>();
        int ans = 0, i = 0, j = 0;
        while (i < n && j < n) {
            // try to extend the range [i, j]
            if (!set.contains(s.charAt(j))){
                set.add(s.charAt(j++));
                ans = Math.max(ans, j - i);
            }
            else {
                set.remove(s.charAt(i++));
            }
        }
        return ans;
    }
	
	public static int lengthOfLongestSubstring2(String s) {
        int n = s.length(), ans = 0;
        Map<Character, Integer> map = new HashMap<Character, Integer>(); // current index of character
        // try to extend the range [i, j]
        for (int j = 0, i = 0; j < n; j++) {
            if (map.containsKey(s.charAt(j))) {
                i = Math.max(map.get(s.charAt(j)), i);
            }
            ans = Math.max(ans, j - i + 1);
            map.put(s.charAt(j), j + 1);
        }
        return ans;
    }
	
	 public static int maxArea(int[] height) {
	        int maxarea = 0, l = 0, r = height.length - 1;
	        while (l < r) {
	            maxarea = Math.max(maxarea, Math.min(height[l], height[r]) * (r - l));
	            if (height[l] < height[r])
	                l++;
	            else
	                r--;
	        }
	        return maxarea;
	    }
	 
	 public static List<List<Integer>> threeSum(int[] num) {
		    Arrays.sort(num);
		    List<List<Integer>> res = new LinkedList<List<Integer>>(); 
		    for (int i = 0; i < num.length-2; i++) {
		        if (i == 0 || (i > 0 && num[i] != num[i-1])) {
		            int lo = i+1, hi = num.length-1, sum = 0 - num[i];
		            while (lo < hi) {
		                if (num[lo] + num[hi] == sum) {
		                    res.add(Arrays.asList(num[i], num[lo], num[hi]));
		                    while (lo < hi && num[lo] == num[lo+1]) lo++;
		                    while (lo < hi && num[hi] == num[hi-1]) hi--;
		                    lo++; hi--;
		                } else if (num[lo] + num[hi] < sum) lo++;
		                else hi--;
		           }
		        }
		    }
		    return res;
		}
	 
	 
	 public ListNode removeNthFromEnd(ListNode head, int n) {
		    
		    ListNode start = new ListNode(0);
		    ListNode slow = start, fast = start;
		    slow.next = head;
		    
		    //Move fast in front so that the gap between slow and fast becomes n
		    for(int i=1; i<=n+1; i++)   {
		        fast = fast.next;
		    }
		    //Move fast to the end, maintaining the gap
		    while(fast != null) {
		        slow = slow.next;
		        fast = fast.next;
		    }
		    //Skip the desired node
		    slow.next = slow.next.next;
		    return start.next;
		}
	 
	 public static int removeDuplicates1(int[] A) {
		    if (A.length==0) return 0;
		    int j=0;
		    for (int i=0; i<A.length; i++)
		        if (A[i]!=A[j]) A[++j]=A[i];
		    System.out.println(j+1);
		    return ++j;
		}
	 public static int removeDuplicates(int[] A) {  
		    if(A == null || A.length==0)  
		        return 0;  
		    int index = 1;  
		    for(int i=1;i<A.length;i++)  
		    {  
		        if(A[i]!=A[i-1])  
		        {  
		            A[index]=A[i];  
		            index++;  
		        }  
		    }  		   
		    return index-1;  
		} 
	 
	 public static List<Integer> findSubstring(String s, String[] words) {
	        final Map<String, Integer> counts = new HashMap<>();
	        for (final String word : words) {
	            counts.put(word, counts.getOrDefault(word, 0) + 1);
	        }
	        final List<Integer> indexes = new ArrayList<Integer>();
	        final int n = s.length(), num = words.length, len = words[0].length();
	        for (int i = 0; i < n - num * len + 1; i++) {
	            final Map<String, Integer> seen = new HashMap<>();
	            int j = 0;
	            while (j < num) {
	                final String word = s.substring(i + j * len, i + (j + 1) * len);
	                if (counts.containsKey(word)) {
	                    seen.put(word, seen.getOrDefault(word, 0) + 1);
	                    if (seen.get(word) > counts.getOrDefault(word, 0)) {
	                        break;
	                    }
	                } else {
	                    break;
	                }
	                j++;
	            }
	            if (j == num) {
	                indexes.add(i);
	            }
	        }
	        return indexes;
	    }
}
  class ListNode {
     int val;
     ListNode next;
     ListNode(int x) { val = x; }
 }