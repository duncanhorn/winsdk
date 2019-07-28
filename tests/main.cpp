
int unique_handle_tests();
int event_tests();

int main()
{
    int result = 0;
    result += unique_handle_tests();
    result += event_tests();
    return result;
}
