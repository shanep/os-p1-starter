#include <stdlib.h>
#include <lab.h>
#include <gtest/gtest.h>

static int *alloc_data(int i)
{
     int *rval = (int *)malloc(sizeof(int));
     *rval = i;
     return rval;
}

static void destroy_data(void *data)
{
     free(data);
}

static int compare_to(const void *a, const void *b)
{
     int fst = *(int *)a;
     int snd = *(int *)b;
     return fst - snd;
}

/**
 * @brief Create a list with 0 elements for testing
 * 
 */
class ListWith0 : public testing::Test
{
protected:
     void SetUp() override
     {
          this->lst_ = list_init(destroy_data, compare_to);
     }

     void TearDown() override
     {
          list_destroy(&lst_);
     }

     list_t *lst_ = nullptr;
};

/**
 * @brief Test Fixture that will create a list with 5 elements to
 * use with testing.
 * 
 */
class ListWith5 : public testing::Test
{
protected:
     void SetUp() override
     {
          this->lst_ = list_init(destroy_data, compare_to);
          for (int i = 0; i < 5; i++)
          {
               list_add(lst_, alloc_data(i));
          }
          EXPECT_EQ(lst_->size, 5);
     }

     void TearDown() override
     {
          list_destroy(&lst_);
     }

     list_t *lst_ = nullptr;
};

TEST_F(ListWith0, add1)
{
     list_add(lst_, alloc_data(1));
     EXPECT_EQ(lst_->size, 1);
     //With one node both next and prev should be equal
     EXPECT_EQ(lst_->head->next, lst_->head->prev);
     //Make sure we didn't clobber our sentinel node
     EXPECT_NE(lst_->head, lst_->head->next);
     EXPECT_NE(lst_->head, lst_->head->prev);
     EXPECT_EQ(lst_->head->data, nullptr);

     //Check to make sure our data actually made it into the node
     //Check both next and prev links to make sure we are properly linked
     EXPECT_EQ(*((int *)lst_->head->next->data), 1);
     EXPECT_EQ(*((int *)lst_->head->prev->data), 1);
}
