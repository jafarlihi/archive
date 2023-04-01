import { Button, Form, Input } from 'antd';
import React, { useEffect } from 'react';
import styled from 'styled-components';
import { toast } from 'react-toastify';
import { useNavigate } from 'react-router-dom';

const Center = styled.div`
  position: absolute;
  left: 50%;
  top: 50%;
  transform: translate(-50%, -50%);
`;

const Login: React.FC = () => {
  const navigate = useNavigate();

  useEffect(() => {
    if (localStorage.getItem('access'))
      navigate('/jobs');
  }, []);

  const onFinish = async (values: any) => {
    const formData = new FormData();
    formData.append('username', values.username);
    formData.append('password', values.password);
    const response = await (await fetch(
      process.env.REACT_APP_API_URL + '/auth/jwt/create/', {
        method: 'POST',
        body: formData,
      },
    )).json();
    if (!response.access)
      toast('Username or password is wrong');
    else {
      localStorage.setItem('access', response.access);
      localStorage.setItem('refresh', response.refresh);
      navigate('/jobs');
    }
  };

  const onFinishFailed = (errorInfo: any) => {
  };

  return (
    <Center>
      <Form
        name="basic"
        labelCol={{ span: 8 }}
        wrapperCol={{ span: 16 }}
        initialValues={{ remember: true }}
        onFinish={onFinish}
        onFinishFailed={onFinishFailed}
        autoComplete="off"
      >
        <Form.Item
          label="Username"
          name="username"
          rules={[{ required: true, message: 'Please input your username!' }]}
        >
          <Input />
        </Form.Item>

        <Form.Item
          label="Password"
          name="password"
          rules={[{ required: true, message: 'Please input your password!' }]}
        >
          <Input.Password />
        </Form.Item>

        <Form.Item wrapperCol={{ offset: 8, span: 16 }}>
          <Button type="primary" htmlType="submit">
            Log in
          </Button>
        </Form.Item>
      </Form>
    </Center>
  );
};

export default Login;
