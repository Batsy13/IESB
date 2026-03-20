def get_all_substrings(string):
    def recursive_substrings(s, start, end, result):
        if start == len(s):
            return result
        
        if end > len(s):
            return recursive_substrings(s, start + 1, start + 1, result)
        
        if start != end:
            result.append(s[start:end])
            
        return recursive_substrings(s, start, end + 1, result)

    return recursive_substrings(string, 0, 1, [])

input_str = "abc"
print(get_all_substrings(input_str))