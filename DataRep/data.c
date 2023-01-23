#include <data.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int convertCharToNumber(char ch) {
  if (ch >= '0' && ch <= '9') {
    return ch - '0';
  } else if (ch >= 'A' && ch <= 'F') {
    return ch - 'A' + 10;
  } else {
    return -1;
  }
}

char convertNumberToChar(int n) {
  if (n >= 0 && n <= 9) {
    return n + '0';
  } else if (n >= 10 && n <= 15) {
    return n - 10 + 'A';
  } else {
    return 0;
  }
}

Data convert_to_base_n(Data src, unsigned char n) {
    Data new_data;
    new_data.data = NULL;
    // TODO
    Data j = {0, 0, 0, 0, src.data};
    int base_10 = 0;
    int length = (int)(src.len - 1);
    for (int i = length; i >= 0; i--) {
      base_10 += convertCharToNumber(j.data->number) * pow((int)src.base, i);
      j.data = j.data->next;
      if (j.data == NULL) {
        break;
      }
    }
    int count = 0;
    new_data.base = n;
    new_data.sign = src.sign;
    new_data.number_bits = src.number_bits;
    Data old_n;
    old_n.data = NULL;
    while ((base_10 / n) != 0 || (base_10 % n) != 0) {
        DataNode *new_node = (DataNode *) malloc(sizeof(DataNode));
        if (new_node == NULL) {
            printf("malloc failed.\n");
        }
        new_node->next = old_n.data;
        old_n.data = new_node;
        new_node->number = convertNumberToChar(base_10 % n);
        base_10 = base_10 / n;
        count++;
    }
    new_data.len = (unsigned char)count;
    new_data.data = old_n.data;
    return new_data;
}

int convert_to_int(Data src) {
  // TODO
  int result = 0;

  if (((int)src.sign) == 1) {
    Data new_data = convert_to_base_n(src, 2);
    int length = (int)(new_data.len);
    if ((new_data.data->number == '1') && (((int)new_data.number_bits) == ((int)new_data.len))) {
      result = -pow(2, length - 1) * convertCharToNumber(new_data.data->number);
      DataNode *head = new_data.data->next;
      for (int i = length - 2; i >= 0; i--) {
        result += pow(2, i) * convertCharToNumber(head->number);
        head = head->next;
      }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
    } else if (((int)new_data.number_bits) != ((int)new_data.len)) {
      DataNode *head = new_data.data;
      for (int i = length - 1; i >= 0; i--) {
        result += pow(2, i) * convertCharToNumber(head->number);
        head = head->next;
      }
    }
  } else if (((int)src.sign) == 0) {
    Data j = {0, 0, 0, 0, src.data};
    int length = (int)(src.len - 1);
    for (int i = length; i >= 0; i--) {
      result += convertCharToNumber(j.data->number) * pow((int)src.base, i);
      j.data = j.data->next;
      if (j.data == NULL) {
        break;
      }
    }
  }
  if (src.data == NULL || (src.data->number == '0' && src.data->next == NULL)) {
    return 0;
  }
    return result;
}

Data left_shift(Data src, int n) {
  Data new_data;
  // TODO
  new_data = convert_to_base_n(src, 2);
  int length = (int)(new_data.len);
  DataNode *tail = (DataNode *) malloc(sizeof(DataNode));
  if (tail == NULL) {
      printf("malloc failed.\n");
  }
  tail = new_data.data;
  while (tail->next != NULL) {
    tail = tail->next;
  }
  printf("\ntail node: %c\n", tail->number);
  for (int i = n; i > 0; i--) {
    DataNode *tailNext = (DataNode *) malloc(sizeof(DataNode));
    if (tailNext == NULL) {
      printf("malloc failed.\n");
    }
    tailNext->number = '0';
    tailNext->next = NULL;

    tail->next = tailNext;
    tail = tail->next;
    length++;
  }
  while (((length) > (int)(new_data.number_bits)) && (new_data.data != NULL)) {
    new_data.data = new_data.data->next;
    length -= 1;
  }
  while ((new_data.data->number == '0') && (new_data.data != NULL)) {
    new_data.data = new_data.data->next;
    length -= 1;
    if (new_data.data->next == NULL) {
      break;
    }
  }
  // int lengthCheck = 0;
  // while (new_data.data != NULL) {
  //   lengthCheck++;
  //   new_data.data = new_data.data->next;
  // }
  

  new_data.len = (unsigned char)length;
  return new_data;
}

Data right_shift(Data src, int n) {
  Data new_data;
  // TODO
  new_data = convert_to_base_n(src, 2);
  int length = (int)(new_data.len);
  if(n > length || n > (int)(new_data.number_bits)){
     n = length;
  }
  if (((int)new_data.sign) == 1 && ((int)new_data.number_bits) == length) {
    if(n == (length - 1)) {
      DataNode *temp = malloc(sizeof(DataNode));
      *temp = (DataNode){new_data.data->number, 0};
      new_data.data = temp;
      length= 1; 
    } else {
      for (int i = n; i > 0; i--) {
        DataNode *nthNode = (DataNode *) malloc(sizeof(DataNode));
        if (nthNode == NULL) {
          printf("malloc failed.\n");
        }
        nthNode = new_data.data;
        while (nthNode != NULL) {
          if (nthNode->next->next == NULL) {
            break;
          } else {
            nthNode = nthNode->next;
          }
        }
        if (nthNode == NULL && new_data.data == NULL) {
          new_data.data = NULL;
          break;
        }
        nthNode->next = NULL;
        length -= 1;
      }
    }
    DataNode *old_n = new_data.data;
    for (int i = n; i > 0; i--) {
      DataNode *new_node = (DataNode *) malloc(sizeof(DataNode));
      if (new_node == NULL) {
        printf("malloc failed.\n");
      }
      new_node->next = old_n;
      new_node->number = '1';
      old_n = new_node;
      length += 1;
    }
    new_data.data = old_n;
    new_data.len = (unsigned char)length;
  } else {
    for (int i = n; i > 0; i--) {
      DataNode *nthNode = (DataNode *) malloc(sizeof(DataNode));
      if (nthNode == NULL) {
        printf("malloc failed.\n");
      }
      nthNode = new_data.data;
      while ((nthNode != NULL)) {
          if (nthNode->next->next == NULL) {
            break;
          } else {
          nthNode = nthNode->next;
          }
      }
      if (nthNode == NULL) {
        new_data.data = NULL;
        break;
      }
      nthNode->next = NULL;
      length -= 1;
    }
    // while ((new_data.data->number == '0') && (new_data.data != NULL)) {
    //   new_data.data = new_data.data->next;
    //   length -= 1;
    //   if (new_data.data->next == NULL) {
    //     break;
    //   }
    // }
    new_data.len = (unsigned char)length;
    
  }
  return new_data;
}

